import numpy as np
print("请输入N:", end=' ')
N = int(input())
print(f'矩阵的规模为{N*2}行{N*2}列，随机生成此规模矩阵为：')
nums = 4*N*N
myMat = np.random.randint(0, 10, size=(2*N, 2*N))
print(myMat)
A1 = myMat[0:N, 0:N]
A2 = myMat[0:N, N:2*N]
A3 = myMat[N:2*N, 0:N]
A4 = myMat[N:2*N, N:2*N]
#print(f'A1={A1}\nA2={A2}\nA3={A3}\nA4={A4}')
myAver = np.zeros((2, 2))#创建一个全0的2*2数组，用于存放四个象限的平均值
myAver[0][0] = np.average(A1)
myAver[0][1] = np.average(A2)
myAver[1][0] = np.average(A3)
myAver[1][1] = np.average(A4)
print(f'myAver={myAver}')

