import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import Binarizer
from sklearn.naive_bayes import BernoulliNB
from sklearn.metrics import accuracy_score
from utils import load_images,load_labels

def binarize_images(images, threshold=128):
    return (images > threshold).astype(np.uint8)

# 加载FASHION-MNIST数据集
train_images = load_images('data/fashionmnist/train-images-idx3-ubyte')
train_labels = load_labels('data/fashionmnist/train-labels-idx1-ubyte')
test_images = load_images('data/fashionmnist/t10k-images-idx3-ubyte')
test_labels = load_labels('data/fashionmnist/t10k-labels-idx1-ubyte')

# 数据预处理
train_images = binarize_images(train_images)
test_images = binarize_images(test_images)

# 将图像数据展平
train_images_flat = train_images.reshape(train_images.shape[0], -1)
test_images_flat = test_images.reshape(test_images.shape[0], -1)

# 初始化并训练朴素贝叶斯分类器
nb_classifier = BernoulliNB()
nb_classifier.fit(train_images_flat, train_labels)

# 在测试集上进行预测
test_predictions = nb_classifier.predict(test_images_flat)

# 计算准确率
accuracy = accuracy_score(test_labels, test_predictions)
print(f'Test Accuracy: {accuracy * 100:.2f}%')

def visualize_predictions(images, true_labels, pred_labels, num_samples=10):
    plt.figure(figsize=(10, 4))  # 调整图的大小
    for i in range(num_samples):
        plt.subplot(2, 5, i + 1)  # 2行5列
        plt.imshow(images[i], cmap='gray')
        plt.title(f'True:{true_labels[i]}\nPred:{pred_labels[i]}')
        plt.axis('off')
    plt.tight_layout()
    plt.savefig(fname='./fashion_bayes_mnist_figure')

visualize_predictions(test_images, test_labels, test_predictions)
results_df = pd.DataFrame({
    'True Label': test_labels,
    'Predicted Label': test_predictions
})
results_df.to_csv('task2_fashion_mnist_sklearn_test_predictions.csv', index=False)