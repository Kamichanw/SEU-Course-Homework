from func import *
from picture import *
from mind import *
#读取数据
def read_images(file_path):
    with open(file_path, 'rb') as f:
        # 读取头部信息
        magic_number = int.from_bytes(f.read(4), byteorder='big')
        num_images = int.from_bytes(f.read(4), byteorder='big')
        num_rows = int.from_bytes(f.read(4), byteorder='big')
        num_cols = int.from_bytes(f.read(4), byteorder='big')

        # 读取图像数据（每张图像是 28x28 的字节数组）
        image_data = np.frombuffer(f.read(), dtype=np.uint8)
        images = image_data.reshape(num_images, num_rows, num_cols)

    return images

def read_labels(file_path):
    with open(file_path, 'rb') as f:
        # 读取头部信息
        magic_number = int.from_bytes(f.read(4), byteorder='big')
        num_labels = int.from_bytes(f.read(4), byteorder='big')

        # 读取标签数据
        labels = np.frombuffer(f.read(), dtype=np.uint8)

    return labels
def one_hot(labels):
    y = np.zeros((len(labels), 10))
    y[np.arange(len(labels)), labels] = 1
    return y
# 读取训练集
X_train = read_images('./data/mnist/train/train-images.idx3-ubyte')# (60000, 28, 28)
y_train = read_labels('./data/mnist/train/train-labels.idx1-ubyte')# (60000,)
# 读取测试集
X_test = read_images('./data/mnist/test/t10k-images.idx3-ubyte')# (10000, 28, 28)
y_test = read_labels('./data/mnist/test/t10k-labels.idx1-ubyte')# (10000,)

#标准化 归一化到[0,1]
X_train = X_train/255.0
X_test = X_test/255.0
mean_train=np.mean(X_train)
std_train=np.std(X_train)

print(mean_train,std_train)
X_train=(X_train-mean_train)/std_train
X_test=(X_test-mean_train)/std_train

#展平图像数据
X_train = X_train.reshape(-1, 28 * 28)
X_test = X_test.reshape(-1, 28 * 28)

# 生成One-hot编码
y_train = one_hot(y_train)
y_test = one_hot(y_test)

input_size = 28*28
hidden_size = 256
output_size = 10

model = NeuralNetwork(input_size, hidden_size, output_size,0.01,10)
# 训练参数
losses,acc = model.fit(X_train,y_train,X_test, y_test,100)
prediction = model.predict(X_test)
print(f"测试集准确率: {acc[-1]*100:.4f}%")

model1 = NeuralNetwork_Mindspore(input_size, hidden_size, output_size,0.001,10)
# 训练参数
losses1,acc1= model1.fit(X_train,y_train,X_test, y_test,100)
prediction1 = model1.predict(X_test).asnumpy()
print(f"测试集准确率: {acc1[-1]*100:.4f}%")

#acc曲线 loss曲线
picture0(losses,acc)
#mindspore 对比
picture1(losses,acc,losses1,acc1)
pre={
    'NeuralNetwork':prediction,
        'Mindspore':prediction1,
}
save_predictions(pre,'prediction-mnist.csv')