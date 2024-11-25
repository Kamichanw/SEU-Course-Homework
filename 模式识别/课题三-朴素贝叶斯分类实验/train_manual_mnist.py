from matplotlib import pyplot as plt
import pandas as pd
from utils import *
import numpy as np

class NaiveBayesClassifier:
    def __init__(self):
        self.class_priors = None
        self.feature_probs = None

    def fit(self, X, y):
        n_samples, n_features = X.shape
        self.classes = np.unique(y)
        n_classes = len(self.classes)

        # 计算每个类别的先验概率
        self.class_priors = np.zeros(n_classes)
        for idx, c in enumerate(self.classes):
            self.class_priors[idx] = np.sum(y == c) / n_samples

        # 计算每个特征在每个类别中的条件概率
        self.feature_probs = np.zeros((n_classes, n_features, 2))
        for idx, c in enumerate(self.classes):
            X_c = X[y == c]
            self.feature_probs[idx, :, 1] = (np.sum(X_c, axis=0) + 1) / (X_c.shape[0] + 2)  # 平滑
            self.feature_probs[idx, :, 0] = 1 - self.feature_probs[idx, :, 1]

    def predict(self, X):
        n_samples, n_features = X.shape
        log_priors = np.log(self.class_priors)
        log_probs = np.zeros((n_samples, len(self.classes)))

        for i in range(n_samples):
            for idx, c in enumerate(self.classes):
                log_likelihood = np.sum(np.log(self.feature_probs[idx, np.arange(n_features), X[i]]), axis=0)
                log_probs[i, idx] = log_likelihood + log_priors[idx]

        return self.classes[np.argmax(log_probs, axis=1)]


def binarize_images(images, threshold=128):
    return (images > threshold).astype(np.uint8)


# 加载数据集
train_images = load_images('data/mnist/train-images.idx3-ubyte')
train_labels = load_labels('data/mnist/train-labels.idx1-ubyte')
test_images = load_images('data/mnist/t10k-images.idx3-ubyte')
test_labels = load_labels('data/mnist/t10k-labels.idx1-ubyte')

# 数据预处理
train_images = binarize_images(train_images)
test_images = binarize_images(test_images)

# 训练模型
# 将图像数据展平
train_images_flat = train_images.reshape(train_images.shape[0], -1)
test_images_flat = test_images.reshape(test_images.shape[0], -1)

# 初始化并训练朴素贝叶斯分类器
nb_classifier = NaiveBayesClassifier()
nb_classifier.fit(train_images_flat, train_labels)

# 在测试集上进行预测
test_predictions = nb_classifier.predict(test_images_flat)

# 计算准确率
accuracy = np.mean(test_predictions == test_labels)
print(f'Test Accuracy: {accuracy * 100:.2f}%')

def visualize_predictions(images, true_labels, pred_labels, num_samples=10):
    plt.figure(figsize=(10, 4))  # 调整图的大小
    for i in range(num_samples):
        plt.subplot(2, 5, i + 1)  # 2行5列
        plt.imshow(images[i], cmap='gray')
        plt.title(f'True:{true_labels[i]}\nPred:{pred_labels[i]}')
        plt.axis('off')
    plt.tight_layout()
    plt.savefig(fname='./bayes_mnist_figure')

visualize_predictions(test_images, test_labels, test_predictions)
results_df = pd.DataFrame({
    'True Label': test_labels,
    'Predicted Label': test_predictions
})
results_df.to_csv('task1_mnist_manual_test_predictions.csv', index=False)