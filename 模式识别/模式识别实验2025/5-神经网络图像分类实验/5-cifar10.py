from func import *
from picture import *
from mind import *
#读取数据
def load_data(file_path):
    with open(file_path, 'rb') as f:
        data = f.read()
    images = []
    labels = []
    # 每张图片占用3073字节（1字节标签 + 3072字节像素）
    for i in range(10000):
        # 提取标签（第1字节）
        label = data[i * 3073]
        # 提取像素数据（后3072字节）
        pixels = data[(i * 3073 + 1): (i + 1) * 3073]
        # 转换为numpy数组并调整形状为(32, 32, 3)
        img = np.frombuffer(pixels, dtype=np.uint8).reshape(3, 32, 32).transpose(1, 2, 0)
        labels.append(label)
        images.append(img)
    return np.array(images), np.array(labels)
# 生成One-hot编码
def one_hot(labels):
    y = np.zeros((len(labels), 10))
    y[np.arange(len(labels)), labels] = 1
    return y
# 数据加载配置
train_path = ['./data/cifar10/train/data_batch_1.bin',
               './data/cifar10/train/data_batch_2.bin',
               './data/cifar10/train/data_batch_3.bin',
               './data/cifar10/train/data_batch_4.bin',
               './data/cifar10/train/data_batch_5.bin']
test_path = './data/cifar10/test/test_batch.bin'
X_train, y_train = [], []
for f in train_path:
    images, labels = load_data(f)
    labels = one_hot(labels)
    X_train.append(images)
    y_train.append(labels)
#将5个 (10000, 3072) 的数组合并为一个 (50000, 3072) 的数组
X_train = np.vstack(X_train)
y_train = np.vstack(y_train)
#归一化至[0,1]
X_train = X_train / 255.0
#标准化
mean_train=np.mean(X_train,axis=(0,1,2))#三通道均值
std_train=np.std(X_train,axis=(0,1,2))#三通道标准差
X_train = (X_train-mean_train)/std_train

 # 加载测试数据
images, labels = load_data(test_path)
images =images / 255.0
X_test = (images-mean_train)/std_train

#展平图像数据
X_train = X_train.reshape(-1, 32*32*3)
X_test = X_test.reshape(-1, 32*32*3)
#生成one_hot编码
y_test = one_hot(labels)

# 初始化模型
input_size = 32*32*3
hidden_size = 256
output_size = 10

model = NeuralNetwork(input_size, hidden_size, output_size,0.01,30)
# 训练参数
losses,acc = model.fit(X_train,y_train,X_test, y_test,100)
prediction = model.predict(X_test)
print(f"测试集准确率: {acc[-1]*100:.4f}%")

model1 = NeuralNetwork_Mindspore(input_size, hidden_size, output_size,0.001,9)
# 训练参数
losses1,acc1= model1.fit(X_train,y_train,X_test, y_test,100)
prediction1 = model1.predict(X_test).asnumpy()
print(f"测试集准确率: {acc1[-1]*100:.4f}%")

#acc曲线 loss曲线
picture0(losses,acc)
picture0(losses1,acc1)
#mindspore 对比
picture1(losses,acc,losses1,acc1)

pre={
    'NeuralNetwork':prediction,
        'Mindspore':prediction1,
}
save_predictions(pre,'prediction.csv')