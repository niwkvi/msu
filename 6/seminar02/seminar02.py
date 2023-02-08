with open('104.csv', 'r') as f_in:
    data = [i.rstrip().split(',') for i in f_in]

TRACK_ID_index = data[0].index('TRACK_ID')
X_index = data[0].index('X')
Y_index = data[0].index('Y')

IDs = {data[i][TRACK_ID_index] for i in range(1, len(data))}
objects_num = len(IDs)

path_len_max = 0

for ID in IDs:
    x = [float(data[i][X_index]) for i in range(1, len(data)) if data[i][TRACK_ID_index] == ID]
    y = [float(data[i][Y_index]) for i in range(1, len(data)) if data[i][TRACK_ID_index] == ID]

    path_len = 0
    for i in range(len(x) - 1):
        path_len += ((x[i] - x[i + 1]) ** 2 + (y[i] - y[i + 1]) ** 2) ** 0.5

    if path_len > path_len_max:
        path_len_max = path_len

with open('seminar02.csv', 'w') as f_out:
    f_out.write('task1,task2\n')
    f_out.write(str(objects_num) + ',' + str(round(path_len_max, 2)))
