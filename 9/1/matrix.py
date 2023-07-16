import numpy as np

with open('../txt-files/mxn.txt', 'r') as f:
    m, n = map(int, f.read().split())

status = input('Enter 0 to generate matrix A and vector x\nEnter 1 to calculate vector b\n')
while not status.isdigit() and (status != '0' or status != '1'):
    status = input('Try again:\n')

if status == '0':
    matrix = np.random.randint(1, 100, (m, n))
    x = np.random.randint(1, 100, (n, 1))
    np.savetxt('matrix.txt', matrix, fmt='%i')
    np.savetxt('x.txt', x, fmt='%i')

elif status == '1':
    matrix = np.loadtxt('matrix.txt')
    x = np.loadtxt('x.txt')
    b = matrix.dot(x)
    np.savetxt('b.txt', b, fmt='%i')
