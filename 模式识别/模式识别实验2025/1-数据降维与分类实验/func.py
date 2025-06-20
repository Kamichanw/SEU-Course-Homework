import pandas as pd
import os
import numpy as np
import random
from sklearn.decomposition import PCA
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis as LDA
from sklearn.linear_model import LogisticRegression as LR
class LogisticRegression:
    def __init__(self, learning_rate=0.01, iterations=500):
        self.lr = learning_rate  # 学习率
        self.iterations = iterations  # 迭代次数
        self.weights = None  # 权重参数
        self.loss_history= []
        self.acc_history=[]
    def fit(self, X, y, X_test, y_test):
        # 在特征矩阵右侧拼接一列1(常数项)
        X = np.hstack((X, np.ones((X.shape[0], 1))))
        # 随机初始化参数（包括偏置项）
        random.seed(12)
        np.random.seed(12)
        self.weights = np.random.randn(X.shape[1])

        # 梯度下降优化
        for i in range(self.iterations):
            # 线性组合（矩阵乘法）
            #X(n_sample,n_feature) w(n_feature,1) X.T*w.T(1,n_sample)
            linear = self.weights.T @ X.T
            p = 1 / (1 + np.exp(-linear))

            #记录交叉熵损失loss,防止log(0)
            loss = -np.mean(y * np.log(p + 1e-10) +(1 - y) * np.log(1 - p + 1e-10))
            self.loss_history.append(loss)

            # 计算梯度,沿负梯度方向更新
            grad = (p - y) @ X / len(y)
            self.weights -= self.lr * grad
            pre,acc = self.evaluate(X_test,y_test)
            self.acc_history.append(acc)
        #print(np.argmax(self.acc_history))
    #准确率
    def evaluate(self, X, y):
        # 添加偏置项后进行预测
        X = np.hstack((X, np.ones((X.shape[0], 1))))

        # 计算概率并使用0.5作为阈值
        prob=1 / (1 + np.exp(-X @ self.weights))
        pre=(prob >= 0.5).astype(int)

        acc=np.sum(pre==y)/len(y)
        return pre,acc

def pca(X, n_components):
    # 计算协方差矩阵,rowvar=False表示每列是一个特征
    cov = np.cov(X, rowvar=False)
    # 特征分解（返回特征值和特征向量）
    eig_vals, eig_vecs = np.linalg.eigh(cov)

    # 按特征值从大到小排序的索引，[::-1]实现逆序
    sorted_idx = np.argsort(eig_vals)[::-1]
    # 选取前n个特征向量作为主成分
    indices =sorted_idx[0:n_components]
    components = eig_vecs[:,indices]
    return components,eig_vals[sorted_idx]

def lda(X, y):
    # 按类别分割数据
    X0 = X[y == 0]# 红葡萄酒
    X1 = X[y == 1]# 白葡萄酒
    # 计算类别均值向量
    m = np.mean(X,axis=0)
    m0 = np.mean(X0, axis=0)
    m1 = np.mean(X1, axis=0)

    # 类内散度矩阵Sw
    Sw = (X0 - m0).T @ (X0 - m0) + (X1 - m1).T @ (X1 - m1)
    # 类间散度矩阵Sb
    m0 = np.expand_dims(m0, axis=1)
    m1 = np.expand_dims(m1, axis=1)
    Sb = len(X0)*((m0 - m) @ (m0 - m))+len(X1)*((m1 - m) @ (m1 - m))
    # Sw的伪逆
    Sw_inv = np.linalg.pinv(Sw)

    # 特征值 特征向量
    eig_vals, eig_vecs = np.linalg.eig(Sw_inv @ Sb)
    # 最大特征值的索引
    max_eig_vals=np.argmax(eig_vals)
    #选取对应特征向量（reshape为列向量）
    max_eig_vec=eig_vecs[:, max_eig_vals].real.reshape(-1,1)
    return max_eig_vec
#保存测试集到CSV文件
def save_test(test_dict, filename):
    df = pd.DataFrame(test_dict)
    df.to_csv(os.path.join('data', filename), index=False)
#保存预测结果到CSV文件
def save_predictions(y_true, predictions_dict, filename):
    df = pd.DataFrame(predictions_dict)
    df['true_label'] = y_true
    df.to_csv(os.path.join('results', filename), index=False)