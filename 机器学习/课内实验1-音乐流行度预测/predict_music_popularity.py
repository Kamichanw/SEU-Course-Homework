import numpy as np
import pandas as pd
from scipy import stats
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
from statsmodels.stats.outliers_influence import variance_inflation_factor
from sklearn.decomposition import PCA
from scipy.interpolate import interp1d
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt

# 数据预处理
# 数据集需要和该脚本放在同级目录下
df = pd.read_csv('./song_data.csv')

df = df.drop('song_name', axis=1).drop_duplicates()  # 删去重复冗余的行
attributes = df.columns.drop('song_popularity')
discrete_attributes = ['key', 'time_signature', 'audiomode']  # 直接列举离散属性
continous_attributes = [attr for attr in attributes if attr not in discrete_attributes]  # 使用Python中的列表推导式导出数据集连续属性

print(continous_attributes)

# 离散数据连续化：使用one-hot编码
df = pd.get_dummies(df, columns=discrete_attributes[:2])

# 连续数据处理
# 对数据集进行异常值的处理:使用四分位距方法剔除超过3个标准差的值
for attr in continous_attributes:
    Q1, Q3 = df[attr].quantile(0.25), df[attr].quantile(0.75)
    IQR = Q3 - Q1
    df = df[(Q1 - 1.5 * IQR <= df[attr]) & (df[attr] <= (Q3 + 1.5 * IQR))].reset_index(drop=True)

# 连续数据归一化:使用MinMaxScaler方法将数据归一化到[0,1]
scaler = MinMaxScaler()
df[continous_attributes] = scaler.fit_transform(df[continous_attributes])

# 划分数据集：80%作为训练集，20%作为测试集
X = df.drop('song_popularity', axis=1)
y = df['song_popularity']
train_X, test_X, train_y, test_y = train_test_split(X, y, test_size=0.2, train_size=0.8, random_state=42)

# 多重共线性检查：使用VIF方差膨胀因子
numeric_X = X.select_dtypes(include=[np.number])
vif_df = pd.DataFrame()
vif_df["variables"] = numeric_X.columns
vif_df["VIF"] = [variance_inflation_factor(numeric_X, i) for i in range(numeric_X.shape[1])]
print(vif_df)

# 多重共线性检查处理：使用PCA主成分分析法
if np.any(vif_df['VIF'] > 5):
    pca = PCA().fit(train_X)
    x_values = range(1, pca.n_components_ + 1)
    threshold = 0.95
    f = interp1d(x_values, np.cumsum(pca.explained_variance_ratio_), kind="linear")
    # cumulative_explained_variance累计解释方差
    cev_x = np.linspace(1, pca.n_components_, 1000)
    cev_y = f(cev_x)
    index = np.argwhere(np.isclose(cev_y, [threshold] * len(cev_y), atol=1e-3)).flatten()
    index = index[int(len(index) / 2)]

    pca = PCA(n_components=int(cev_x[index]))
    train_X = pd.DataFrame(pca.fit_transform(train_X))
    test_X = pd.DataFrame(pca.fit_transform(test_X))

    LR_model = LinearRegression().fit(train_X, train_y)
    train_prediction = LR_model.predict(train_X)
    test_prediction = LR_model.predict(test_X)
    print('Coefficients\n', LR_model.coef_)
    print('Intercepts', LR_model.intercept_)

    f, axes = plt.subplots(2, 3, sharey=True)
    rc = np.random.choice(range(0, pca.n_components_), len(axes[0]), replace=False)

    for i, col in enumerate(rc):
        axes[0][i].set_title(f'Training set {i + 1}')
        axes[0][i].scatter(train_X[col], train_y, label='real', color='skyblue')
        axes[0][i].scatter(train_X[col], train_prediction, label='pred', color='lightgreen')
        axes[0][i].legend()
    for i, col in enumerate(rc):
        axes[1][i].set_title(f'Test set {i + 1}')
        axes[1][i].scatter(test_X[col], test_y, label='real', color='skyblue')
        axes[1][i].scatter(test_X[col], test_prediction, label='pred', color='lightgreen')
        axes[1][i].legend()

# 打印训练集和测试集上的MSE和R2分数
print('MSE of Training set', mean_squared_error(train_y, train_prediction))
print('R2-Score of Training set', r2_score(train_y, train_prediction))
print('MSE of Test set', mean_squared_error(test_y, test_prediction))
print('R2-Score of Test set', r2_score(test_y, test_prediction))

# 展示预测结果
plt.show()
