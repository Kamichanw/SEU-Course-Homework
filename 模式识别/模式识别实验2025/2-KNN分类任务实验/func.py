import random
import numpy as np
import pandas as pd
import os
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score

#NCA
class Mahalanobis:
    def __init__(self, learning_rate=0.002, iterations=50,features=4, e=2):
        random.seed(31)
        np.random.seed(31)
        self.lr = learning_rate  # 学习率
        self.iterations = iterations  # 迭代次数
        self.features = features#特征数
        self.e = e#降到2维
        self.A =np.sqrt(2.0 / (self.features + self.e))*np.random.randn(self.e,self.features)
        # Xavier初始A矩阵 2*4 X[i]:4*1 X[i].T:1*4
        self.loss_history=[]
    #计算p矩阵 p[i][j]：ij同类的概率 p[i]:样本i所有同类样本概率之和，即i被正确分类概率
    def calc_p(self, X, y):
        #X[:, None]在第二个维度添加一个新轴97*1*4 X[None, :]在第一个维度前添加新轴1*97*4
        # diff[i][j][k]=X[i][k]-X[j][k] 97*97*4 diff(i,j)即向量X[i]-X[j]
        diff = X[:, None] - X[None, :]
        # 计算 Mahalanobis距离 X.T@A.T
        d = diff @ self.A.T
        d2 = -np.sum(d ** 2,axis=-1)
        # 排除 i=j 的情况
        prob = np.exp(d2) * (1 - np.eye(X.shape[0], X.shape[0]))
        prob /= (np.sum(prob, axis=1) + 1e-10)
        # y[i]=y[j] mask[i][j]=1 else mask[i][j]=0
        mask = (y[:, None] == y[None, :]).squeeze()
        # 按行求和
        prob_row = np.sum(prob * mask, axis=1)
        # 损失计算
        loss = -np.sum(np.log(prob_row + 1e-10))
        return prob,prob_row,loss
    def fit(self, X, y):
        n_samples = X.shape[0]
        #梯度下降
        for iteration in range(self.iterations):
            # 梯度
            gradients = np.zeros((self.e, self.features))
            # p矩阵
            prob,prob_row,loss = self.calc_p(X,y)
            self.loss_history.append(loss)

            #对每个样本i
            for i in range(n_samples):
                #遍历所有样本j
                for j in range(n_samples):
                    if i==j:
                        continue
                    outer=np.outer(X[i] - X[j],X[i] - X[j])
                    gradients += 2*prob_row[i]*prob[i][j]*(self.A@outer)
                    #j与i同类
                    if y[i] == y[j]:
                        gradients -= 2*prob[i][j]*(self.A@outer)
            #更新A
            self.A+=self.lr*gradients

# k近邻
def KNN(k,X_train,y_train,X,A):
#待分类条目X A矩阵（马氏距离使用）返回label
    dis=[]
    for i in range(0,len(X_train)):
        d=A@(X-X_train[i])
        dis.append(d.T@d)
    # 按距离从小到大排序的索引
    sorted_idx = np.argsort(dis)
    #前k个索引
    indices = sorted_idx[0:k]
    y_choose=y_train[indices]
    label=np.zeros(3)
    #获取最近k个训练样本的标签
    for i in range(0,3):
        label[i]=np.sum(y_choose==i)
    #判为最多的一类
    max_index=label.argmax();
    return max_index

def evaluate(K,X,y,X1,y1,A):
    # 训练集(X,y) 测试集(X1,y1) 矩阵A
    acc=[]
    pre=[]
    for k in range(1, 11):
        predict = []
        for i in range(0, len(X1)):
            predict.append(KNN(k, X, y, X1[i], A))
        acc.append(sum(y1==predict) / (len(y1)))
        if k==K:
            pre=predict
    acc = [float(element) for element in acc]
    pre = [int(element) for element in pre]
    return acc,pre

#sklearn准确率
def evaluate_sklearn(K,X,y,X1,y1,A):
    # 训练集(X,y) 测试集(X1,y1) 矩阵A
    acc = []
    pre = []
    for k in range(1, 11):
        predict = []
        knn = KNeighborsClassifier(
            n_neighbors=k,  # K值
            metric='mahalanobis',
            metric_params={'VI': A.T@A}  # 传入逆协方差矩阵
        )
        knn.fit(X, y)
        y_pred = knn.predict(X1)
        acc.append(accuracy_score(y1, y_pred))
        if k == K:
            pre = y_pred
    return acc, pre
def save_data(test_dict, filename):
    df = pd.DataFrame(test_dict)
    df.to_csv(os.path.join('data', filename), index=False)
#保存预测结果到CSV文件
def save_predictions(predictions_dict, filename):
    df = pd.DataFrame(predictions_dict)
    df.to_csv(os.path.join('results', filename), index=False)