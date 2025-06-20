import random
import numpy as np
import mindspore as ms
from mindspore import nn, ops, Tensor, Parameter
class Mahalanobis_Mindspore(nn.Cell):
    def __init__(self, learning_rate=0.001, iterations=50, features=4, e=2):
        super().__init__()
        self.lr = learning_rate
        self.iterations = iterations
        self.features = features
        self.e = e
        self.A = None
        self.history = []
        self.grad_var_history = []
        self.optimizer=None

    def forward(self, X, y):
        X = X.astype(ms.float32)
        y = y.astype(ms.int32)
        n = X.shape[0]

        # 向量化计算所有样本对的距离
        diff = X[:, None] - X[None, :]

        # 计算 Mahalanobis 距离 (n, n, e) -> (n, n)
        d = ops.matmul(diff, self.A.T)
        d2 = -ops.sum(d ** 2, dim=-1)

        # 排除 i=j 的情况
        prob = ops.exp(d2) * (1 - ops.eye(X.shape[0], X.shape[0], ms.float32))
        prob /= (ops.sum(prob, dim=1, keepdim=True) + 1e-10)  # 归一化
        # y[i]=y[j] mask[i][j]=1 else mask[i][j]=0
        mask = (y[:, None] == y[None, :]).squeeze()
        # 按行求和
        prob_row = ops.sum(prob * mask, dim=1)
        # 损失计算
        loss = -ops.sum(ops.log(prob_row + 1e-10))
        return loss

    def fit(self, X, y):
        X = Tensor(X, ms.float32)
        y = Tensor(y, ms.int32).reshape(-1,1)

        random.seed(31)
        np.random.seed(31)
        self.A = Parameter(Tensor(np.sqrt(2.0 / (self.features + self.e))* np.random.randn(self.e, self.features),ms.float32)
                           , name='A',requires_grad=True)
        #余弦退火
        cosine_decay_lr = nn.CosineDecayLR(min_lr=self.lr, max_lr=0.04, decay_steps=self.iterations)
        self.optimizer = nn.Adam([self.A], cosine_decay_lr)
        # 定义前向网络和优化器
        grad_fn = ms.value_and_grad(self.forward, None, [self.A])

        for iteration in range(self.iterations):
            # 计算损失和梯度
            loss, grads = grad_fn(X, y)
            #print(grads[0].asnumpy())
            # 获取梯度张量并计算梯度平方
            grad_np = grads[0].asnumpy()  # 将梯度转换为NumPy数组
            grad_var = np.sum(grad_np**2)  # 计算梯度平方
            # 更新参数
            self.optimizer(grads)
            # 记录损失
            self.history.append(loss.asnumpy())
            self.grad_var_history.append(grad_var)