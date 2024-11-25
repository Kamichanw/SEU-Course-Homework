import numpy as np
import pandas as pd
from cvxopt import matrix, solvers
from sklearn.metrics import classification_report,accuracy_score
import matplotlib.pyplot as plt

def svm_qp(X, y):
    m, n = X.shape
    y = y.astype(float)
    
    # Create the P, q, G, h matrices for the QP solver
    K = np.dot(X, X.T) * np.outer(y, y)
    P = matrix(K)
    q = matrix(-np.ones((m, 1)))
    G = matrix(np.diag(-np.ones(m)))
    h = matrix(np.zeros(m))
    A = matrix(y.reshape(1, -1))
    b = matrix(np.zeros(1))

    # Solve QP problem
    sol = solvers.qp(P, q, G, h, A, b)
    alphas = np.array(sol['x']).flatten()
    
    # Compute weight vector w
    w = np.sum(alphas[:, None] * y[:, None] * X, axis=0)
    
    # Compute bias term b
    support_vectors = (alphas > 1e-5)
    b = np.mean(y[support_vectors] - np.dot(X[support_vectors], w))
    
    return w, b, alphas

# Example usage
X = np.array([[2, 3], [3, 3], [4, 3], [1, 1], [2, 1], [3, 1]])
y = np.array([1, 1, 1, -1, -1, -1])

w, b, alphas = svm_qp(X, y)
print("Weights:", w)
print("Bias:", b)


class SVM:
    def __init__(self, C=1.0, tol=1e-3, max_passes=5):
        self.C = C
        self.tol = tol
        self.max_passes = max_passes

    def fit(self, X, y):
        m, n = X.shape
        self.X = X
        self.y = y
        self.alphas = np.zeros(m)
        self.b = 0
        self.E = np.zeros(m)
        self.K = np.dot(X, X.T)
        
        passes = 0
        while passes < self.max_passes:
            num_changed_alphas = 0
            for i in range(m):
                self.E[i] = self._E(i)
                if (y[i] * self.E[i] < -self.tol and self.alphas[i] < self.C) or \
                   (y[i] * self.E[i] > self.tol and self.alphas[i] > 0):
                    j = np.random.choice([_ for _ in range(m) if _ != i])
                    self.E[j] = self._E(j)
                    
                    alpha_i_old = self.alphas[i].copy()
                    alpha_j_old = self.alphas[j].copy()
                    
                    if y[i] != y[j]:
                        L = max(0, self.alphas[j] - self.alphas[i])
                        H = min(self.C, self.C + self.alphas[j] - self.alphas[i])
                    else:
                        L = max(0, self.alphas[j] + self.alphas[i] - self.C)
                        H = min(self.C, self.alphas[j] + self.alphas[i])
                        
                    if L == H:
                        continue
                        
                    eta = 2 * self.K[i, j] - self.K[i, i] - self.K[j, j]
                    if eta >= 0:
                        continue
                    
                    self.alphas[j] -= y[j] * (self.E[i] - self.E[j]) / eta
                    self.alphas[j] = np.clip(self.alphas[j], L, H)
                    
                    if abs(self.alphas[j] - alpha_j_old) < 1e-5:
                        continue
                        
                    self.alphas[i] += y[i] * y[j] * (alpha_j_old - self.alphas[j])
                    
                    b1 = self.b - self.E[i] - y[i] * (self.alphas[i] - alpha_i_old) * self.K[i, i] - \
                         y[j] * (self.alphas[j] - alpha_j_old) * self.K[i, j]
                    b2 = self.b - self.E[j] - y[i] * (self.alphas[i] - alpha_i_old) * self.K[i, j] - \
                         y[j] * (self.alphas[j] - alpha_j_old) * self.K[j, j]
                    
                    if 0 < self.alphas[i] < self.C:
                        self.b = b1
                    elif 0 < self.alphas[j] < self.C:
                        self.b = b2
                    else:
                        self.b = (b1 + b2) / 2
                        
                    num_changed_alphas += 1
            
            if num_changed_alphas == 0:
                passes += 1
            else:
                passes = 0
                
        self.w = np.dot((self.alphas * y).T, X)
        
    def _E(self, i):
        return self.b + np.dot(self.alphas * self.y, self.K[:, i]) - self.y[i]
    
    def predict(self, X):
        return np.sign(np.dot(X, self.w) + self.b)

X_train = pd.read_csv('breast_cancer_Xtrain.csv', header=0).values
X_test = pd.read_csv('breast_cancer_Xtest.csv', header=0).values

y_train = np.ravel(pd.read_csv('breast_cancer_Ytrain.csv', header=0).values)
y_test = np.ravel(pd.read_csv('breast_cancer_Ytest.csv', header=0).values)

classifier = SVM(C=2)

classifier.fit(X_train, y_train)

y_pred = classifier.predict(X_test)

accuracy = accuracy_score(y_test, y_pred)
print(f"Test accuracy：{accuracy:.4f}")
print(f"{classification_report(y_true=y_test,y_pred=y_pred)}")


# 加载数据
X_train = pd.read_csv('breast_cancer_Xtrain.csv', header=0).values[:, :2]  # 只选前两个特征
X_test = pd.read_csv('breast_cancer_Xtest.csv', header=0).values[:, :2]

y_train = np.ravel(pd.read_csv('breast_cancer_Ytrain.csv', header=0).values)
y_test = np.ravel(pd.read_csv('breast_cancer_Ytest.csv', header=0).values)

classifier = SVM(C=2)

classifier.fit(X_train, y_train)

y_pred = classifier.predict(X_test)

x_min, x_max = X_train[:, 0].min() - 1, X_train[:, 0].max() + 1
y_min, y_max = X_train[:, 1].min() - 1, X_train[:, 1].max() + 1
xx, yy = np.meshgrid(np.linspace(x_min, x_max, 500), np.linspace(y_min, y_max, 500))

# 预测整个网格的值
Z = classifier.predict(np.c_[xx.ravel(), yy.ravel()])
Z = Z.reshape(xx.shape)

# 绘制决策边界和数据点
plt.contourf(xx, yy, Z, alpha=0.8)
plt.scatter(X_train[:, 0], X_train[:, 1], c=y_train, edgecolors='k')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.title('SVC with linear kernel')
plt.show()