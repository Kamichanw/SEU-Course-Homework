import numpy as np
import mindspore as ms
from mindspore import nn, ops, Tensor, Parameter
class Mindspore_LogisticRegression:
    def __init__(self, learning_rate=0.01, iterations=500):
        self.lr = learning_rate
        self.iterations = iterations
        self.weights = None
        self.loss_history = []
        self.acc_history = []
        self.optimizer = None

    def forward(self, X, y):
    #前向计算函数
        logits = ops.matmul(X, self.weights)
        prob = ops.sigmoid(logits)
        loss = ops.mean(-y * ops.log(prob + 1e-8) - (1 - y) * ops.log(1 - prob + 1e-8))
        return loss

    def fit(self, X, y, X_test, y_test):
        # 数据预处理
        X = Tensor(X, ms.float32)
        y = Tensor(y, ms.float32).reshape(-1, 1)

        # 添加偏置项
        X = ops.cat([X, ops.ones((X.shape[0], 1), X.dtype)], axis=1)

        # 参数初始化
        np.random.seed(12)
        self.weights = Parameter(Tensor(np.random.randn(X.shape[1], 1).astype(np.float32)),name='weights',requires_grad=True)
        self.optimizer = nn.Adam([self.weights],learning_rate=self.lr)
        grad = ms.value_and_grad(self.forward,grad_position=None,weights=[self.weights])

        # 训练循环
        for iteration in range(self.iterations):
            loss, grads = grad(X, y)
            self.optimizer(grads)
            self.loss_history.append(float(loss))
            pre, acc = self.evaluate(X_test, y_test)
            self.acc_history.append(acc)
        #print(np.argmax(self.acc_history))
    def evaluate(self, X, y):
        X = Tensor(X, ms.float32)
        y = Tensor(y, ms.int32)
        X = ops.cat([X, ops.ones((X.shape[0], 1), X.dtype)], axis=1)
        prob = ops.sigmoid(ops.matmul(X, self.weights))
        pre = (prob >= 0.5).astype(int).flatten()
        acc=ops.sum(pre==y)/y.shape[0]
        return pre,acc.asnumpy()