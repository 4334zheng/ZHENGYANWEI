import math
import numpy as np

#(a)
print("a代码运行结果：")
mysqrt = [math.sqrt(x) for x in range(0,5)]
mycrt = [x**(1/3) for x in range(0,5)]
npData = np.array(mysqrt)
print("The shape:", npData.shape)
print("The dimensionality:", npData.ndim)
print("The type:", npData.dtype)
twoDarray = np.array([mysqrt, mycrt])
print("The shape:", twoDarray.shape)
print("The dimensionality:", twoDarray.ndim)
print("The type:", twoDarray.dtype)

#(b)
print("-------------\nb代码运行结果：")
zeros = np.zeros(3)
zMat = np.zeros((4,3))
ones = np.ones(3)
oMat = np.ones((3,2))
diag = np.eye(4)
rng = np.arange(5)
dm = np.diag(rng)
print(dm.shape)
zMat_re = zMat.reshape(6,2)

#(c)
print("-------------\nc代码运行结果：")
A = np.random.randint(0, 10, size = (3,2))
B = np.random.randint(0, 10, size = (3,3,3))
C = np.random.randint(0, 10, size = (3,1))
print(A**2)
print(np.sqrt(A))
print(A + C)
print(B + C)
B[:, 0:2, 0:2] -= 20
print(B)

#(d)
print("-----------\nd代码运行结果：")
from numpy import linalg
A = np.array([[2, 1, -2],[1,-1,-1], [1, 1 ,3]])
b = np.array([3, 0, 12])
x = linalg.solve(A,b)
print(x)