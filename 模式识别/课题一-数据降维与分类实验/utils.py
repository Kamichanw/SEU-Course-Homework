import numpy as np


def accuracy(y_true, y_pred):
    return sum(y_true == y_pred) / len(y_true)


def train_test_split(X, y, test_size=0.2, random_state=None):
    if random_state is not None:
        np.random.seed(random_state)

    num_samples = X.shape[0]
    num_test_samples = int(test_size * num_samples)

    shuffled_indices = np.random.permutation(num_samples)
    test_indices = shuffled_indices[:num_test_samples]
    train_indices = shuffled_indices[num_test_samples:]

    X_train = X[train_indices]
    y_train = y[train_indices]
    X_test = X[test_indices]
    y_test = y[test_indices]

    return X_train, X_test, y_train, y_test


class LogisticRegression:
    def __init__(self, lr=0.01, epochs=1000):
        self.lr = lr
        self.epochs = epochs
        self.beta = None
        self.history = None

    def fit(self, X, y):
        X = np.c_[X, np.ones((X.shape[0], 1))]
        num_samples, num_features = X.shape
        num_classes = np.max(y) + 1
        self.beta = np.zeros((num_features, num_classes))

        self.history = []
        for _ in range(self.epochs):
            model = X @ self.beta
            y_preds = self._softmax(model)
            self.history.append({
                'train loss':
                self._cross_entropy(self._one_hot_encode(y, num_classes),
                                    y_preds)
            })
            grad = X.T @ (y_preds -
                          self._one_hot_encode(y, num_classes)) / num_samples
            self.beta -= self.lr * grad

    def predict(self, X):
        X = np.c_[X, np.ones((X.shape[0], 1))]
        model = np.dot(X, self.beta)
        y_preds = self._softmax(model)
        return np.argmax(y_preds, axis=1)

    def _softmax(self, z):
        e = np.exp(z - np.max(z, axis=1, keepdims=True))
        return e / np.sum(e, axis=1, keepdims=True)

    def _cross_entropy(self, y_true, y_pred):
        epsilon = 1e-10
        y_pred = np.clip(y_pred, epsilon, 1.0 - epsilon)
        return -np.mean(np.sum(y_true * np.log(y_pred), axis=1))

    def _one_hot_encode(self, y, num_classes):
        return np.eye(num_classes)[y].astype(float)


class PCA:
    def __init__(self, n_components=None):
        self.n_components = n_components
        self.components_ = None
        self.explained_variance_ratio_ = None
        self.explained_variance_ = None
        self.n_features_ = None
        self.n_samples_ = None

    def fit(self, X):
        self.n_features_ = X.shape[1]
        self.n_samples_ = X.shape[0]
        n = self.n_samples_
        self.mean = np.mean(X, axis=0)
        X_centered = X - self.mean
        R = 1 / (n - 1) * (X_centered.T @ X_centered)
        Lambda, Alpha = np.linalg.eig(R)
        eigen_pair = sorted(
            [(l, a) for l, a in zip(Lambda, Alpha.T)],
            reverse=True,
            key=lambda pair: pair[0],
        )
        ev = [(lambda_i / sum(Lambda)) for lambda_i, _ in eigen_pair]
        cev = np.cumsum(ev)

        if self.n_components is None:
            self.n_components = self.n_features_
        elif isinstance(self.n_components, float):
            self.n_components = np.argwhere(cev <= self.n_components).shape[0]

        self.components_ = np.stack(
            [pair[1] for pair in eigen_pair[: self.n_components]], axis=1
        )
        self.explained_variance_ratio_ = cev[: self.n_components]
        self.explained_variance_ = np.array(
            [pair[0] for pair in eigen_pair[: self.n_components]]
        )
        return self

    def fit_transform(self, X):
        return self.fit(X).transform(X)

    def transform(self, X):
        if self.components_ is None:
            raise AttributeError(
                "This PCA instance is not fitted yet. Call 'fit' with appropriate arguments before using this estimator."
            )
        X_centered = X - self.mean
        return X_centered @ self.components_


class LDA:
    def __init__(self, n_components=None):
        self.n_components = n_components
        self.coef_ = None
        self.means_ = None
        self.classes_ = None
        self.n_features_in_ = None
        self.xbar_ = None  # overall mean

    def fit_transform(self, X, y):
        return self.fit(X, y).transform(X)

    def fit(self, X, y):
        self.classes_ = np.unique(y)
        self.n_features_in_ = X.shape[1]

        if self.n_components is None:
            self.n_components = len(self.classes_) - 1

        self.means_ = np.array(
            [np.mean(X[y == label], axis=0) for label in self.classes_])
        self.xbar_ = np.mean(X, axis=0)

        Sw = sum([(X[y == label] - self.means_[i]).T
                  @ (X[y == label] - self.means_[i])
                  for i, label in enumerate(self.classes_)])
        Sw += np.eye(Sw.shape[0]) * 1e-8

        Sb = sum([
            X[y == label].shape[0] * (self.means_[i] - self.xbar_).reshape(
                -1, 1) @ (self.means_[i] - self.xbar_).reshape(1, -1)
            for i, label in enumerate(self.classes_)
        ])

        Lambda, Alpha = np.linalg.eigh(np.linalg.inv(Sw) @ Sb)
        sorted_indices = np.argsort(Lambda)[::-1]
        self.coef_ = Alpha[:, sorted_indices[:self.n_components]]

        return self

    def transform(self, X):
        if self.coef_ is None:
            raise AttributeError(
                "This LDA instance is not fitted yet. Call 'fit' with appropriate arguments before using this estimator."
            )
        return X @ self.coef_

