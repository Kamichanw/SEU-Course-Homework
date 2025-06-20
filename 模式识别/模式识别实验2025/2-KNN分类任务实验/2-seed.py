from func import *
from picture import *
import numpy as np

# 读取文件，处理缺失值和格式错误
data = []
with open("./data/seeds_dataset.txt", "r") as f:
    for line in f:
        # 按制表符分割行，并过滤空字符串
        row = [x.strip() for x in line.split("\t") if x.strip()]
        data.append(row)

# 转换为 NumPy 数组
data = np.array(data, dtype=np.float32)
np.random.seed(12)
np.random.shuffle(data)#打乱顺序

# 提取特征矩阵和标签向量
X = data[:, :-1]  # 前7列是特征
y = data[:, -1].astype(np.int32)  # 最后一列是标签
y = y-1

# 按7:1:2比例划分训练集,验证集，测试集
split1 = int(0.7 * len(X))
split2 = int(0.8 * len(X))
X_train, X_val, X_test = X[:split1],X[split1:split2], X[split2:]
y_train, y_val, y_test = y[:split1],y[split1:split2], y[split2:]

mean_train = np.mean(X_train, axis=0)  # 训练集各特征均值
std_train = np.std(X_train, axis=0)  # 训练集各特征标准差
X_train = (X_train - mean_train) / std_train  # 标准化训练集
X_val = (X_val - mean_train) / std_train  # 标准化验证集
X_test = (X_test - mean_train) / std_train  # 标准化测试集

#验证集
#欧式距离
A=np.eye(7)#单位矩阵
acc_Euclide,pred0=evaluate(1,X_train,y_train,X_val,y_val,A)
#sklearn
acc_Euclide_sklearn,pred3=evaluate_sklearn(1,X_train,y_train,X_val,y_val,A)
#马氏距离
Mahalanobis1=Mahalanobis(iterations=60,features=7, e=3)
Mahalanobis1.fit(X_train,y_train)
acc_Mahalanobis,pred1=evaluate(1,X_train,y_train,X_val,y_val,Mahalanobis1.A)
#sklearn
acc_Mahalanobis_sklearn,pred2=evaluate_sklearn(1,X_train,y_train,X_val,y_val,Mahalanobis1.A)

#准确率对比
picture2(acc_Euclide,acc_Mahalanobis,acc_Euclide_sklearn,acc_Mahalanobis_sklearn)

print('test:')
#测试集
#欧式距离
acc_Euclide,pred0=evaluate(6,X_train,y_train,X_test,y_test,np.eye(7))
acc_Euclide_sklearn,pred3=evaluate_sklearn(6,X_train,y_train,X_test,y_test,np.eye(7))
print('欧式距离:')
print(f"{acc_Euclide[5]:.4f}")
print('欧式距离(sklearn):')
print(f"{acc_Euclide_sklearn[5]:.4f}")
#马氏距离
acc_Mahalanobis,pred1=evaluate(6,X_train,y_train,X_test,y_test,Mahalanobis1.A)
acc_Mahalanobis_sklearn,pred2=evaluate_sklearn(6,X_train,y_train,X_test,y_test,Mahalanobis1.A)
print('马式距离:')
print(f"{acc_Mahalanobis[5]:.4f}")
print('马式距离(sklearn):')
print(f"{acc_Mahalanobis_sklearn[5]:.4f}")

save_data(X_test,'test_seed.csv')
predictions = {
    'y_true':y_test,
    'Euclide': pred0,
    'sklearn-Euclide': pred3,
    'Mahalanobis': pred1,
    'sklearn-Mahalanobis': pred2,
}
save_predictions(predictions, 'predictions_seed.csv')