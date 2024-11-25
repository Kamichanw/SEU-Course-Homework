import numpy as np
import copy
import pandas as pd
import random
from sklearn.metrics import accuracy_score, classification_report

class SVM():
    def __init__(self, kernel='linear', C=1.0, epsilon=1e-6, max_passes=50):
        self.kernel = kernel  # 内核类型
        self.C = C  # 惩罚参数
        self.epsilon = epsilon  # 容忍度
        self.max_passes = max_passes  # 最大迭代次数

        self.w = None
        self.b = None
        self.alphas = None

        self.support_ = None
        self.support_vectors_ = None
        self.dual_coef_ = None
        self.intercept_ = None

    def kernel_function(self, X1, X2):
        # 实现线性核函数
        if self.kernel == 'linear':
            return np.dot(X1, X2)
        else:
            raise ValueError("Unknown type of kernel function.")

    def fit(self, X, y):
        # 获得样本数及其维数
        n, d = np.shape(X)
        self.b = 0.0
        self.alphas = np.zeros((n, 1))
        passes = 0
        
        while passes < self.max_passes:
            alpha_changed = 0
            print(f'beginning: {passes, alpha_changed}')
            for i in range(n):
                Ei = self._compute_error(X, y, i)
                if not self._check_KKT(y, i, Ei):
                    j = self._get_j(i, n)
                    Xi, Xj = X[i, :], X[j, :]
                    Ej = self._compute_error(X, y, j)

                    # calculate alpha_j_new_unc
                    alpha_i_old = copy.deepcopy(self.alphas[i])
                    alpha_j_old = copy.deepcopy(self.alphas[j])
                    eta = self.kernel_function(Xi, Xi) + self.kernel_function(Xj, Xj) - 2 * self.kernel_function(Xi, Xj)
                    alpha_j_new = alpha_j_old + y[j] * (Ei - Ej) / eta

                    # calculate alpha_j_new
                    L, H = self._compute_bounds(y, i, j, alpha_i_old, alpha_j_old)
                    alpha_j_new = self._clip_alpha(alpha_j_new, L, H)
                    alpha_i_new = alpha_i_old + y[i] * y[j] * (alpha_j_old - alpha_j_new)

                    self.alphas[i], self.alphas[j] = alpha_i_new, alpha_j_new

                    self.b = self._compute_bias(X, y, i, j, Ei, Ej, alpha_i_old, alpha_j_old)
                    alpha_changed += 1
            if alpha_changed == 0:
                break
            passes += 1
            print(f'end: {passes, alpha_changed}')
        self.w = self._compute_weights(X, y)

        # Store support vectors, dual coefficients, and intercept
        self.support_ = np.where(self.alphas > 0)[0]
        self.support_vectors_ = X[self.support_]
        self.dual_coef_ = self.alphas * y
        self.intercept_ = self.b

    def _check_KKT(self, y, i, Ei):
        if  (abs(self.alphas[i]) < self.epsilon and y[i] * Ei > -self.epsilon) \
        or ((self.alphas[i] > -self.epsilon and self.alphas[i] < self.C + self.epsilon) and abs(y[i] * Ei) < self.epsilon) \
        or (abs(self.alphas[i] - self.C) < self.epsilon and y[i] * Ei < self.epsilon):
            return True
        return False
        
    def _clip_alpha(self, alpha, L, H):
        if alpha > H:
            alpha = H
        if alpha < L:
            alpha = L

        return alpha

    def _get_j(self, i, n):
        j = i
        while j == i:
            j = int(random.uniform(0, n))
        return j
    
    def _compute_error(self, X, y, i):
        g_xi = np.mean(self.alphas * y * self.kernel_function(X, X[i, :]) + self.b)
        return g_xi - float(y[i])
    
    def _compute_bounds(self, y, i, j, alpha_i_old, alpha_j_old):
        L = None
        H = None
        if y[i] != y[j]:
            L = max(0.0, alpha_j_old - alpha_i_old)
            H = min(self.C, self.C + alpha_j_old - alpha_i_old)
        else:
            L = max(0.0, alpha_j_old + alpha_i_old - self.C)
            H = min(self.C, alpha_j_old + alpha_i_old)
        return (L, H)
    
    def _compute_bias(self, X, y, i, j, Ei, Ej, alpha_i_old, alpha_j_old):
        delta_alpha_i = self.alphas[i] - alpha_i_old
        delta_alpha_j = self.alphas[j] - alpha_j_old

        bi = -Ei - y[i] * self.kernel_function(X[i, :], X[i, :]) * delta_alpha_i - \
             y[j] * self.kernel_function(X[j, :], X[i, :]) * delta_alpha_j + self.b

        bj = -Ej - y[i] * self.kernel_function(X[i, :], X[j, :]) * delta_alpha_i - \
             y[j] * self.kernel_function(X[j, :], X[j, :]) * delta_alpha_j + self.b

        if 0 < self.alphas[i] < self.C and 0 < self.alphas[j] < self.C:
            return bj
        else:
            return (bi + bj) / 2
        
    def _compute_weights(self, X, y):
        return np.mean(self.alphas * y * X, axis=0)
    
    def predict(self, X):
        return np.sign(np.dot(X, self.w) + self.b)
            
X_train = pd.read_csv('breast_cancer_Xtrain.csv', header=0).values
X_test = pd.read_csv('breast_cancer_Xtest.csv', header=0).values

y_train = pd.read_csv('breast_cancer_Ytrain.csv', header=0).values
y_test = pd.read_csv('breast_cancer_Ytest.csv', header=0).values

classifier = SVM(C=2)

classifier.fit(X_train, y_train)

y_pred = classifier.predict(X_test)

accuracy = accuracy_score(y_test, y_pred)
print(f"Test accuracy：{accuracy:.4f}")
print(f"{classification_report(y_true=y_test, y_pred=y_pred)}")
