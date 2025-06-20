import matplotlib.pyplot as plt
#iris acc 对比mindspore
def picture0(acc_Euclide,acc_Mahalanobis,acc_Mahalanobis_Mindspore):
    plt.figure(figsize=(15, 5))  # 创建画布
    plt.subplot(1, 3, 1)  # 1行3列的第1个子图
    plt.plot(acc_Euclide)
    plt.xlabel('K')
    plt.ylabel('Acc')
    plt.title('Euclid')
    plt.xticks(ticks=range(0, 10), labels=range(1, 11))

    plt.subplot(1, 3, 2)  # 1行3列的第2个子图
    plt.plot(acc_Mahalanobis)
    plt.xlabel('K')
    plt.ylabel('Acc')
    plt.title('Mahalanobis')
    plt.xticks(ticks=range(0, 10), labels=range(1, 11))

    plt.subplot(1, 3, 3)  # 1行3列的第3个子图
    plt.plot(acc_Mahalanobis_Mindspore)
    plt.xlabel('K')
    plt.ylabel('Acc')
    plt.title('Mindspore')
    plt.xticks(ticks=range(0, 10), labels=range(1, 11))

    plt.tight_layout()
    plt.show()
#iris loss
def picture1(loss_Mahalanobis,loss_Mindspore,iterations):
    plt.figure(figsize=(10, 5))  # 创建画布
    plt.xlim(0, iterations)
    plt.plot(loss_Mahalanobis)
    plt.plot(loss_Mindspore)
    plt.xlabel('Iterations')
    plt.ylabel('Loss')
    plt.show()
#seed acc
def picture2(acc_Euclide,acc_Mahalanobis,acc_Euclide_sklearn,acc_Mahalanobis_sklearn):
    plt.figure(figsize=(20, 5))  # 创建画布
    plt.subplot(1, 4, 1)
    plt.plot(acc_Euclide)
    plt.xlabel('K')
    plt.ylabel('Acc')
    plt.title('Euclid')
    plt.xticks(ticks=range(0, 10), labels=range(1, 11))

    plt.subplot(1, 4, 3)
    plt.plot(acc_Mahalanobis)
    plt.xlabel('K')
    plt.ylabel('Acc')
    plt.title('Mahalanobis')
    plt.xticks(ticks=range(0, 10), labels=range(1, 11))

    plt.subplot(1, 4, 2)
    plt.plot(acc_Euclide_sklearn)
    plt.xlabel('K')
    plt.ylabel('Acc')
    plt.title('sklearn_Euclid')
    plt.xticks(ticks=range(0, 10), labels=range(1, 11))

    plt.subplot(1, 4, 4)
    plt.plot(acc_Mahalanobis_sklearn)
    plt.xlabel('K')
    plt.ylabel('Acc')
    plt.title('sklearn_Mahalanobis')
    plt.xticks(ticks=range(0, 10), labels=range(1, 11))

    plt.tight_layout()
    plt.show()