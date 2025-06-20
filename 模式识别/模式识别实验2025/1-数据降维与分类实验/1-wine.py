from func import *
from picture import *
from mind import *
# 读取葡萄酒数据集
red = pd.read_csv('./data/winequality-red.csv', delimiter=';')
white = pd.read_csv('./data/winequality-white.csv', delimiter=';')

# 添加标签列（红葡萄酒标为0，白葡萄酒标为1）
red['label'] = 0
white['label'] = 1
# 合并两个数据集，axis=0表示纵向合并
data = pd.concat([red, white], axis=0)

# 打乱数据顺序
data = data.sample(frac=1, random_state=151).reset_index(drop=True)
# 提取特征矩阵和标签向量
X = data.drop('label', axis=1).values  # 转换为numpy数组
y = data['label'].values

# 按7:3比例划分训练集和测试集
split = int(0.7 * len(X))  # 分割点索引
X_train, X_test = X[:split], X[split:]  # 前70%作为训练集
y_train, y_test = y[:split], y[split:]  # 后30%作为测试集

#标准化数据
mean_train = np.mean(X_train, axis=0)  # 训练集各特征均值
std_train = np.std(X_train, axis=0)  # 训练集各特征标准差
X_train = (X_train - mean_train) / std_train  # 标准化训练集
X_test = (X_test - mean_train) / std_train  # 标准化测试集

#原始数据
origin = LogisticRegression(iterations=500)
origin.fit(X_train, y_train,X_test,y_test)
# 计算测试集准确率
origin_prediction,acc_origin=origin.evaluate(X_test,y_test)

#mindspore
origin_mindspore=Mindspore_LogisticRegression(iterations=500)
origin_mindspore.fit(X_train, y_train,X_test,y_test)
origin_mindspore_prediction,acc_origin_mindspore=origin_mindspore.evaluate(X_test,y_test)

# PCA
pca_components, eig_vals= pca(X_train, 4)  # 获取主成分向量
# 数据投影
X_train_pca = X_train @ pca_components
X_test_pca = X_test @ pca_components
#预测
pca = LogisticRegression(iterations=500)
pca.fit(X_train_pca, y_train,X_test_pca,y_test)
pca_prediction,acc_pca=pca.evaluate(X_test_pca,y_test)

#mindspore
pca_mindspore=Mindspore_LogisticRegression(iterations=167)
pca_mindspore.fit(X_train_pca, y_train,X_test_pca,y_test)
pca_mindspore_prediction,acc_pca_mindspore=pca_mindspore.evaluate(X_test_pca,y_test)

# LDA
lda_components = lda(X_train, y_train)  
X_train_lda = X_train @ lda_components  # 投影到一维空间
X_test_lda = X_test @ lda_components
#预测
lda = LogisticRegression(iterations=247)
lda.fit(X_train_lda, y_train,X_test_lda,y_test)
lda_prediction,acc_lda=lda.evaluate(X_test_lda,y_test)
#mindspore
lda_mindspore=Mindspore_LogisticRegression(iterations=97)
lda_mindspore.fit(X_train_lda, y_train,X_test_lda,y_test)
lda_mindspore_prediction,acc_lda_mindspore=lda_mindspore.evaluate(X_test_lda,y_test)

#输出准确率
print(f"原始数据准确率: {acc_origin:.4f}")
print(f"PCA后准确率: {acc_pca:.4f}")
print(f"LDA后准确率: {acc_lda:.4f}")
print(f"使用mindspore: ")
print(f"原始数据准确率: {acc_origin_mindspore:.4f}")
print(f"PCA后准确率: {acc_pca_mindspore:.4f}")
print(f"LDA后准确率: {acc_lda_mindspore:.4f}")

#PCA贡献率图像
picture0(eig_vals)
# PCA投影可视化（二维散点图） LDA投影可视化（一维分布直方图）
picture1(X_train_pca,X_train_lda,y_train)
# loss和acc曲线
picture2(origin,pca,lda)
# loss曲线和Acc曲线(对比mindspore)
picture3(origin,pca,lda,origin_mindspore,pca_mindspore,lda_mindspore)

#组织测试集
save_test(X_test, 'test.csv')
# 组织预测结果
predictions = {
    'origin': origin_prediction,
    'origin_mindspore': np.ravel(origin_mindspore_prediction),
    'pca': pca_prediction,
    'pca_mindspore': np.ravel(pca_mindspore_prediction),
    'lda': lda_prediction,
    'lda_mindspore': np.ravel(lda_mindspore_prediction)
}
save_predictions(y_test, predictions, 'predictions.csv')