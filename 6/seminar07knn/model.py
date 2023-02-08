import numpy as np


class KDNode(object):
    def __init__(self, data_indices, data_center, split, left, right):
        self.data_indices = data_indices
        self.data_center = data_center
        self.split = split
        self.left = left
        self.right = right


class KDTree(object):
    def __init__(self, x, y, leaf_size, p):
        self.x = np.array(x)
        self.y = np.array(y)
        self.leaf_size = leaf_size
        self.p = p
        self.x_indices = np.arange(len(x))
        self.root = self.new_kdtree(self.x_indices)

    def new_kdtree(self, x_indices):
        if not len(x_indices) or len(x_indices) < self.leaf_size:
            return None
        else:
            split, data_center = self.new_split(x_indices)
            left = x_indices[self.x[x_indices, split] < data_center]
            right = x_indices[self.x[x_indices, split] >= data_center]
            return KDNode(x_indices, data_center, split, self.new_kdtree(left), self.new_kdtree(right))

    def new_split(self, x_indices):
        variance = np.var(self.x[x_indices], axis=0)
        split = np.argmax(variance)
        data_center = np.median(self.x[x_indices, split])
        return split, data_center

    def search(self, x_i, n_neighbors):
        tree = self.root

        if tree is None:
            return None

        path = self.get_path(x_i, tree, n_neighbors)
        indices = path[-1]

        distances = [self.distance(x_i, self.x[index]) for index in indices]

        dists, labels = zip(*sorted(zip(distances, indices)))
        dists = dists[:n_neighbors]
        labels = labels[:n_neighbors]

        return dists, labels

    def get_path(self, x_i, tree, n_neighbors):
        path = []
        while tree:
            if x_i[tree.split] < tree.data_center:
                path.append(tree.data_indices)
                if tree.left is not None and len(tree.left.data_indices) >= n_neighbors:
                    tree = tree.left
                else:
                    tree = None
            else:
                path.append(tree.data_indices)
                if tree.right is not None and len(tree.right.data_indices) >= n_neighbors:
                    tree = tree.right
                else:
                    tree = None
        return path

    def distance(self, x, y):
        if self.p == 1:
            return np.linalg.norm(x - y, ord=1)
        elif self.p == 2:
            return np.linalg.norm(x - y, ord=2)


class KnnKdtreeRegressor(object):
    def __init__(self, n_neighbors=1, weights='uniform', leaf_size=30, p=1):
        self._n_neighbors = n_neighbors
        self._weights = weights
        self._leaf_size = leaf_size
        self._p = p
        self._kdtree = None

    def fit(self, x, y):
        self.check('fit', x, y)
        self._kdtree = KDTree(x, y, self._leaf_size, self._p)
        return self

    def predict(self, x):
        self.check('predict', x)
        dists, labels = self.kneighbors(x, self._n_neighbors)
        labels = self.voting(dists, labels)
        return labels

    def kneighbors(self, x, n_neighbors):
        results = [self._kdtree.search(x_i, n_neighbors) for x_i in x]
        self.check('results', x, results)
        dists = np.array([result[0] for result in results])
        labels = np.array([result[1] for result in results])
        return dists, labels

    def score(self, y_gt, y_pred):
        if len(y_gt) != len(y_pred):
            raise Exception('The number of predicted labels is not the same as the number of given predictions')
        return np.mean((y_gt - y_pred) ** 2)

    def voting(self, dists, labels):
        results = [0] * len(labels)

        for i in range(len(results)):
            if self._weights == 'uniform':
                weights = np.ones(len(dists[i]))
            elif self._weights == 'distance':
                weights = np.power(dists[i], -1)
                if np.inf in weights:
                    weights = np.isinf(weights)
            elif callable(self._weights):
                weights = self._weights(dists[i])
            else:
                raise Exception('weights is expected to be -uniform-, -distance-, or callable')
            results[i] = self._kdtree.y[labels[i]].dot(weights) / np.sum(weights)

        return results

    def check(self, key, x, y=None):
        if key == 'fit':
            if x is None:
                raise Exception('x is required not to be NaN')
            elif y is None:
                raise Exception('y is required not to be Nan')
            elif len(x) != len(y):
                raise Exception('x and y dimensions are not compatible')
            elif np.isnan(x).any() or np.isinf(x).any():
                raise Exception('x contains NaN or infinity')
            elif np.isnan(y).any() or np.isinf(y).any():
                raise Exception('y contains NaN or infinity')
            elif self._leaf_size is None or type(self._leaf_size) is not int:
                raise Exception('leaf_size is not a number')
            elif self._leaf_size <= 0:
                raise Exception('leaf_size is expected to be > 0')
        elif key == 'predict':
            if x is None:
                raise Exception('x is required not to be NaN')
            elif np.isnan(x).any() or np.isinf(x).any():
                raise Exception('x contains NaN or infinity')
            elif self._kdtree is None:
                raise Exception('Not fitted')
            elif x.shape[1] != self._kdtree.x.shape[1]:
                raise Exception('Not enough features')
            elif self._n_neighbors is None or type(self._n_neighbors) is not int:
                raise Exception('n_neighbors is expected to be > 0')
            elif self._p != 1 and self._p != 2:
                raise Exception('p is expected to be 1 or 2')
        elif key == 'results':
            if len(x) != len(y):
                raise Exception('Not enough neighbors found')
