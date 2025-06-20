import matplotlib.pyplot as plt
import numpy as np

def picture0(eig_vals):
    # 计算贡献率
    variance_ratio = eig_vals / np.sum(eig_vals)
    cumulative_ratio = np.cumsum(variance_ratio)

    # 创建画布和坐标轴
    fig, ax = plt.subplots(figsize=(12, 6))

    # 设置柱状图位置和宽度
    x = np.arange(len(eig_vals))  # 主成分索引
    width = 0.35  # 柱子宽度

    # 绘制方差贡献率柱状图
    bars1 = ax.bar(
        x - width / 2,
        variance_ratio,
        width,
        label='Individual Explained Variance',
        color='tab:blue',
        alpha=0.7
    )

    # 绘制累计贡献率柱状图
    bars2 = ax.bar(
        x + width / 2,
        cumulative_ratio,
        width,
        label='Cumulative Explained Variance',
        color='tab:orange',
        alpha=0.7
    )

    # 标注数值
    def autolabel(bars, ratios):
        #在柱子顶部添加百分比标注
        for bar, ratio in zip(bars, ratios):
            height = bar.get_height()
            ax.text(
                bar.get_x() + bar.get_width() / 2.,
                height + 0.02,
                f'{ratio * 100:.1f}%',
                ha='center',
                va='bottom'
            )

    autolabel(bars1, variance_ratio)
    autolabel(bars2, cumulative_ratio)

    # 设置坐标轴标签和图例
    ax.set_xlabel('Principal Components')
    ax.set_ylabel('Explained Variance Ratio')
    ax.set_xticks(x)
    ax.set_xticklabels([i + 1 for i in x])
    ax.legend(loc='upper left')

    # 设置y轴范围
    ax.set_ylim(0, 1.1)

    plt.title('PCA Explained Variance Ratio Comparison')
    plt.tight_layout()
    plt.show()

def picture1(X_train_pca,X_train_lda,y_train):
    # 可视化展示
    plt.figure(figsize=(12, 5))  # 创建画布

    # PCA投影可视化（二维散点图）
    plt.subplot(1, 2, 1)  # 1行2列的第1个子图
    plt.scatter(X_train_pca[y_train == 0, 0], X_train_pca[y_train == 0, 1], c='blue', alpha=0.5, label='Red')
    plt.scatter(X_train_pca[y_train == 1, 0], X_train_pca[y_train == 1, 1], c='red', alpha=0.5, label='White')
    plt.title('PCA Projection')
    plt.xlabel('Principal Component 1')  # 第一主成分
    plt.ylabel('Principal Component 2')  # 第二主成分
    plt.legend()

    # LDA投影可视化（一维分布直方图）
    plt.subplot(1, 2, 2)
    plt.hist(X_train_lda[y_train == 0], bins=50, alpha=0.5, color='red', label='Red')
    plt.hist(X_train_lda[y_train == 1], bins=50, alpha=0.5, color='blue', label='White')
    plt.title('LDA Projection')
    plt.xlabel('LDA Component')  # 唯一的投影方向
    plt.legend()

    plt.tight_layout()
    plt.show()

def picture2(origin,pca,lda):
    # loss曲线
    plt.figure(figsize=(15, 5))  # 创建画布

    plt.subplot(1, 3, 1)  # 1行3列的第1个子图
    plt.plot(origin.loss_history)
    plt.xlabel('Iterations')
    plt.ylabel('Cross-Entropy Loss')
    plt.title('Origin Training Loss Curve')

    plt.subplot(1, 3, 2)  # 1行3列的第2个子图
    plt.plot(pca.loss_history)
    plt.xlabel('Iterations')
    plt.ylabel('Cross-Entropy Loss')
    plt.title('PCA Training Loss Curve')

    plt.subplot(1, 3, 3)  # 1行3列的第3个子图
    plt.plot(lda.loss_history)
    plt.xlabel('Iterations')
    plt.ylabel('Cross-Entropy Loss')
    plt.title('LDA Training Loss Curve')

    plt.tight_layout()
    plt.show()
    #acc曲线
    plt.figure(figsize=(15, 5))  # 创建画布

    plt.subplot(1, 3, 1)  # 1行3列的第1个子图
    plt.plot(origin.acc_history)
    plt.ylim(0, 1)
    plt.xlabel('Iterations')
    plt.ylabel('Acc')
    plt.title('Origin')

    plt.subplot(1, 3, 2)  # 1行3列的第2个子图
    plt.plot(pca.acc_history)
    plt.ylim(0, 1)
    plt.xlabel('Iterations')
    plt.ylabel('Acc')
    plt.title('PCA')

    plt.subplot(1, 3, 3)  # 1行3列的第3个子图
    plt.plot(lda.acc_history)
    plt.ylim(0,1)
    plt.xlabel('Iterations')
    plt.ylabel('Acc')
    plt.title('LDA')

    plt.tight_layout()
    plt.show()
def picture3(origin,pca,lda,origin_mindspore,pca_mindspore,lda_mindspore):
    # loss曲线
    plt.figure(figsize=(15, 5))  # 创建画布

    plt.subplot(1, 3, 1)  # 1行3列的第1个子图
    plt.plot(origin.loss_history)
    plt.plot(origin_mindspore.loss_history)
    plt.xlabel('Iterations')
    plt.ylabel('Cross-Entropy Loss')
    plt.title('Origin Training Loss Curve')

    plt.subplot(1, 3, 2)  # 1行3列的第2个子图
    plt.plot(pca.loss_history)
    plt.plot(pca_mindspore.loss_history)
    plt.xlabel('Iterations')
    plt.ylabel('Cross-Entropy Loss')
    plt.title('PCA Training Loss Curve')

    plt.subplot(1, 3, 3)  # 1行3列的第3个子图
    plt.plot(lda.loss_history)
    plt.plot(lda_mindspore.loss_history)
    plt.xlabel('Iterations')
    plt.ylabel('Cross-Entropy Loss')
    plt.title('LDA Training Loss Curve')

    plt.tight_layout()
    plt.show()
    #acc曲线
    plt.figure(figsize=(15, 5))  # 创建画布

    plt.subplot(1, 3, 1)  # 1行3列的第1个子图
    plt.plot(origin.acc_history)
    plt.plot(origin_mindspore.acc_history)
    plt.ylim(0, 1)
    plt.xlabel('Iterations')
    plt.ylabel('Acc')
    plt.title('Origin')

    plt.subplot(1, 3, 2)  # 1行3列的第2个子图
    plt.plot(pca.acc_history)
    plt.plot(pca_mindspore.acc_history)
    plt.ylim(0, 1)
    plt.xlabel('Iterations')
    plt.ylabel('Acc')
    plt.title('PCA')

    plt.subplot(1, 3, 3)  # 1行3列的第3个子图
    plt.plot(lda.acc_history)
    plt.plot(lda_mindspore.acc_history)
    plt.ylim(0, 1)
    plt.xlabel('Iterations')
    plt.ylabel('Acc')
    plt.title('LDA')

    plt.tight_layout()
    plt.show()
def picture4(X_train_pca,X_train_pca_sklearn,X_train_lda,X_train_lda_sklearn,y_train):
    plt.figure(figsize=(20, 5))  # 创建画布

    # PCA投影可视化（二维散点图）
    plt.subplot(1, 4, 1)
    plt.scatter(X_train_pca[y_train == 0, 0], X_train_pca[y_train == 0, 1], c='blue', alpha=0.5, label='no')
    plt.scatter(X_train_pca[y_train == 1, 0], X_train_pca[y_train == 1, 1], c='red', alpha=0.5, label='yes')
    plt.title('PCA Projection')
    plt.xlabel('Principal Component 1')  # 第一主成分
    plt.ylabel('Principal Component 2')  # 第二主成分
    plt.legend()

    plt.subplot(1, 4, 2)
    plt.scatter(X_train_pca_sklearn[y_train == 0, 0], X_train_pca_sklearn[y_train == 0, 1], c='blue', alpha=0.5,label='no')
    plt.scatter(X_train_pca_sklearn[y_train == 1, 0], X_train_pca_sklearn[y_train == 1, 1], c='red', alpha=0.5,label='yes')
    plt.title('sklearn-PCA Projection')
    plt.xlabel('Principal Component 1')  # 第一主成分
    plt.ylabel('Principal Component 2')  # 第二主成分
    plt.legend()

    # LDA投影可视化（一维分布直方图）
    plt.subplot(1, 4, 3)
    plt.hist(X_train_lda[y_train == 0], bins=50, alpha=0.5, color='red', label='no')
    plt.hist(X_train_lda[y_train == 1], bins=50, alpha=0.5, color='blue', label='yes')
    plt.title('LDA Projection')
    plt.xlabel('LDA Component')
    plt.legend()

    plt.subplot(1, 4, 4)
    plt.hist(X_train_lda_sklearn[y_train == 0], bins=50, alpha=0.5, color='red', label='no')
    plt.hist(X_train_lda_sklearn[y_train == 1], bins=50, alpha=0.5, color='blue', label='yes')
    plt.title('sklearn-LDA Projection')
    plt.xlabel('sklearn-LDA Component')
    plt.legend()
    plt.tight_layout()
    plt.show()
