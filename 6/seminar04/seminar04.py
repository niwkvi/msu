def print_to_file(filename, data):
    with open(filename, 'w') as f:
        f.writelines(data)


with open('train.csv') as f_in:
    data = [i for i in f_in]

fold_len = len(data) // 2

data1 = data[1:fold_len]
data1.insert(0, data[0])
data2 = data[fold_len:]
data2.insert(0, data[0])

print_to_file('train_1.csv', data1)
print_to_file('val_1.csv', data2)
print_to_file('train_2.csv', data2)
print_to_file('val_2.csv', data1)
