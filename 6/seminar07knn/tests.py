import model

import numpy as np

from sklearn.datasets import fetch_california_housing, make_regression
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsRegressor
from sklearn.metrics import mean_squared_error


def tests(test_num=1, n_neighbors=10, weights='uniform', leaf_size=30, p=1):
    if test_num <= 0:
        raise Exception('Not enough tests')

    print('Number of tests:', test_num)
    print()

    print('errors_test is in progress')
    is_good = errors_test(n_neighbors, weights, leaf_size, p)
    if is_good:
        print('errors_test passed successfully')
        print()
    else:
        print('errors_test failed')
        print()

    print('random_dataset_test is in progress')
    my_score, sk_score = random_dataset_tests(test_num, n_neighbors, weights, leaf_size, p)
    if my_score is None or sk_score is None or len(my_score) != len(sk_score):
        print('random_dataset_tests failed')
        print()
    else:
        print('random_dataset_tests passed successfully')
        print_results(my_score, sk_score)
        print()

    print('california_dataset_test is in progress')
    my_score, sk_score = california_dataset_test(n_neighbors, weights, leaf_size, p)
    if my_score is None or sk_score is None:
        print('california_dataset_test failed')
        print()
    else:
        print('california_dataset_test passed successfully')
        print_results(my_score, sk_score)
        print()

    print('Testing is over')


def print_results(my_score, sk_score):
    print('my_score' + '\t\t' + 'sk_score')

    if not isinstance(my_score, np.ndarray):
        print(str(my_score) + '\t' + str(sk_score))
    else:
        print('\n'.join('{}\t{}'.format(i, j) for i, j in zip(my_score, sk_score)))


def generate_params():
    n_x = np.arange(1000, 20001, 1000)
    n_y = np.arange(10, 101, 5)
    return n_x, n_y


def generate_test():
    n_x, n_y = generate_params()
    n_x = np.random.choice(n_x)
    n_y = np.random.choice(n_y)
    return make_regression(n_samples=n_x, n_features=n_y)


def errors_test(n_neighbors, weights, leaf_size, p):
    is_good = True

    my_model = model.KnnKdtreeRegressor(
        n_neighbors=n_neighbors,
        weights=weights,
        leaf_size=leaf_size,
        p=1
    )

    x, y = generate_test()
    x_train, x_test, y_train, y_test = train_test_split(x, y, train_size=0.8)

    try:
        my_model.fit(x_train, y_train)
    except Exception as e:
        print(str(e))
        is_good = False

    return is_good


def random_dataset_tests(test_num, n_neighbors, weights, leaf_size, p):
    my_score = np.zeros(test_num)
    sk_score = np.zeros(test_num)

    for test_i in range(test_num):
        x, y = generate_test()
        x_train, x_test, y_train, y_test = train_test_split(x, y, train_size=0.8)

        my_model = model.KnnKdtreeRegressor(
            n_neighbors=n_neighbors,
            weights=weights,
            leaf_size=leaf_size,
            p=1
        )
        sk_model = KNeighborsRegressor(
            n_neighbors=n_neighbors,
            weights=weights,
            leaf_size=leaf_size,
            p=1,
            algorithm='kd_tree'
        )

        my_model.fit(x_train, y_train)
        sk_model.fit(x_train, y_train)

        my_result = my_model.predict(x_test)
        sk_result = sk_model.predict(x_test)

        my_score[test_i] = my_model.score(my_result, y_test)
        sk_score[test_i] = mean_squared_error(sk_result, y_test)

    return my_score, sk_score


def california_dataset_test(n_neighbors, weights, leaf_size, p):
    x, y = fetch_california_housing(as_frame=True, return_X_y=True)

    scaler = StandardScaler()
    x = scaler.fit_transform(x)
    y = (y - np.min(y)) / (np.max(y) - np.min(y))

    is_good = np.all(x < 3, axis=1)
    x = x[is_good]
    y = y[is_good]

    x_train, x_test, y_train, y_test = train_test_split(x, y, train_size=0.8)

    my_model = model.KnnKdtreeRegressor(
        n_neighbors=n_neighbors,
        weights=weights,
        leaf_size=leaf_size,
        p=1
    )
    sk_model = KNeighborsRegressor(
        n_neighbors=n_neighbors,
        weights=weights,
        leaf_size=leaf_size,
        p=1,
        algorithm='kd_tree'
    )

    my_model.fit(x_train, y_train)
    sk_model.fit(x_train, y_train)

    my_result = my_model.predict(x_test)
    sk_result = sk_model.predict(x_test)

    my_score = my_model.score(my_result, y_test)
    sk_score = mean_squared_error(sk_result, y_test)

    return my_score, sk_score
