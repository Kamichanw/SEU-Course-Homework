from func import *
from picture import *

# 读取乳腺癌数据集
data = pd.read_csv('./data/breast_cancer_wisconsin.csv', delimiter=',')

# 打乱数据顺序
data = data.sample(frac=1, random_state=151).reset_index(drop=True)
# 提取特征矩阵和标签向量
X = data.drop('target', axis=1).values  # 转换为numpy数组
y = data['target'].values

# 按7:3比例划分训练集和测试集
split = int(0.7 * len(X))  # 分割点索引
X_train, X_test = X[:split], X[split:]  # 前70%作为训练集
y_train, y_test = y[:split], y[split:]  # 后30%作为测试集

#标准化数据
mean_train = np.mean(X_train, axis=0)  # 训练集各特征均值
std_train = np.std(X_train, axis=0)  # 训练集各特征标准差
X_train = (X_train - mean_train) / std_train  # 标准化训练集
X_test = (X_test - mean_train) / std_train  # 标准化测试集

# PCA
pca_components, eig_vals= pca(X_train, 3)  # 获取主成分向量
# 数据投影
X_train_pca = X_train @ pca_components
X_test_pca = X_test @ pca_components
#预测
pca = LogisticRegression(iterations=1000)
pca.fit(X_train_pca, y_train,X_test_pca,y_test)
pca_prediction,acc_pca=pca.evaluate(X_test_pca,y_test)

# LDA
lda_components = lda(X_train, y_train)
X_train_lda = X_train @ lda_components  # 投影到一维空间
X_test_lda = X_test @ lda_components
#预测
lda = LogisticRegression(iterations=324)
lda.fit(X_train_lda, y_train,X_test_lda,y_test)
lda_prediction,acc_lda=lda.evaluate(X_test_lda,y_test)

#输出准确率
print(f"PCA后准确率: {acc_pca:.4f}")
print(f"LDA后准确率: {acc_lda:.4f}")

#sklearn
#PCA
pca_sklearn = PCA(n_components=3)
X_train_pca_sklearn = pca_sklearn.fit_transform(X_train)
X_test_pca_sklearn = pca_sklearn.transform(X_test)

logistic1 = LR(solver='lbfgs',max_iter=1000)
logistic1.fit(X_train_pca_sklearn,y_train)
#预测
pca_prediction_sklearn=logistic1.predict(X_test_pca_sklearn)
acc_pca_sklearn = sum(pca_prediction_sklearn == y_test)/len(pca_prediction_sklearn)
#LDA
lda_sklearn = LDA(n_components=1)
X_train_lda_sklearn = lda_sklearn.fit_transform(X_train,y_train)
X_test_lda_sklearn = lda_sklearn.transform(X_test)

logistic2 = LR(solver='lbfgs',max_iter=324)
logistic2.fit(X_train_lda_sklearn, y_train)
#预测
lda_prediction_sklearn=logistic2.predict(X_test_lda_sklearn)
acc_lda_sklearn = sum(lda_prediction_sklearn == y_test)/len(lda_prediction_sklearn)

print(f"使用sklearn: ")
print(f"PCA后准确率: {acc_pca_sklearn:.4f}")
print(f"LDA后准确率: {acc_lda_sklearn:.4f}")
#PCA贡献率图像
picture0(eig_vals)
picture2(pca,pca,lda)
# PCA投影可视化（二维散点图）对比 LDA投影可视化（一维分布直方图）对比
picture4(X_train_pca,X_train_pca_sklearn,X_train_lda,X_train_lda_sklearn,y_train)
#组织测试集
save_test(X_test, 'test-wisconsin.csv')
# 组织预测结果
predictions = {
    'pca': pca_prediction,
    'pca_sklearn': pca_prediction_sklearn,
    'lda': lda_prediction,
    'lda_sklearn': lda_prediction_sklearn
}
save_predictions(y_test, predictions, 'predictions-wisconsin.csv')

