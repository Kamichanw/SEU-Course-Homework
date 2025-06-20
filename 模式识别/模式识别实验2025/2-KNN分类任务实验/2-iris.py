from func import *
from mind import *
from picture import *
train=pd.read_csv('./data/train.csv')#训练集
val=pd.read_csv('./data/val.csv')#验证集
test=pd.read_csv('./data/test_data.csv')#测试集

X_train=train.drop('label', axis=1).values# 转换为numpy数组
y_train=train['label'].values
X_val=val.drop('label', axis=1).values
y_val=val['label'].values
X_test=test.values
y_test=np.zeros(X_test.shape[0])

#标准化数据
mean_train = np.mean(X_train, axis=0)  # 训练集各特征均值
std_train = np.std(X_train, axis=0)  # 训练集各特征标准差
X_train = (X_train - mean_train) / std_train  # 标准化训练集
X_val = (X_val - mean_train) / std_train  # 标准化验证集
X_test =(X_test - mean_train) / std_train
#验证集
#欧式距离
acc_Euclide,pred=evaluate(1,X_train,y_train,X_val,y_val,np.eye(4))
#马氏距离
Mahalanobis1=Mahalanobis(iterations=100)
Mahalanobis1.fit(X_train,y_train)
acc_Mahalanobis,pred=evaluate(1,X_train,y_train,X_val,y_val,Mahalanobis1.A)
#mindspore
Mahalanobis2=Mahalanobis_Mindspore(iterations=100)
Mahalanobis2.fit(X_train,y_train)
#print(Mahalanobis2.grad_var_history)
acc_Mahalanobis_Mindspore,pred=evaluate(1,X_train,y_train,X_val,y_val,Mahalanobis2.A.asnumpy())

picture0(acc_Euclide,acc_Mahalanobis,acc_Mahalanobis_Mindspore)#k值与acc
picture1(Mahalanobis1.loss_history,Mahalanobis2.history,99)#loss曲线

#测试集
acc,predictions_Euclide=evaluate(6,X_train,y_train,X_test,y_test,np.eye(4))
acc,predictions_Mahalanobis=evaluate(4,X_train,y_train,X_test,y_test,Mahalanobis1.A)
acc,predictions_Mindspore=evaluate(5,X_train,y_train,X_test,y_test,Mahalanobis2.A.asnumpy())

#保存结果
predictions1 = {'label': predictions_Euclide}
predictions2 = {'label': predictions_Mahalanobis}
predictions3 = {'label': predictions_Mindspore}

save_predictions(predictions1, 'task1_test_prediction.csv')
save_predictions(predictions2, 'task2_test_prediction.csv')
save_predictions(predictions3, 'task3_test_prediction.csv')