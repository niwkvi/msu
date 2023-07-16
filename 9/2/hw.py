f = open(r'C:\Users\Gondolin\PycharmProjects\Numerical-Methods\2\out.txt')
li = f.readlines()
li1 = [i[:-1] for i in li]
li2 = li1[::2]

for i in li2:
    print(i)
