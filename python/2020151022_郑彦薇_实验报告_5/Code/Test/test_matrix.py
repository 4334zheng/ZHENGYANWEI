import matrix
n = int(input())
M = []
for i in range(0,n):
    M.append(list(input().split(" ")))
v = list(input().split(","))
i = int(input())
j = int(input())
print("矩阵的维度为：",matrix.matrix_dim(M)) # (a)
print("矩阵与向量v的乘积为：",matrix.mult_M_v(M,v)) # (b)
print("矩阵转置的结果为：",matrix.transpose(M)) # (c)
print("矩阵列元素总和最大为：",matrix.largest_col_sum(M)) # (d)
print("交换第i列和第j列得到矩阵：",matrix.switch_columns(M,i,j)) # (e)