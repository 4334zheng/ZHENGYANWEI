# (a)
''''
def matrix_dim(M):
    lst = []
    lst.append(len(M))
    lst.append(len(M[0]))
    return lst
n = int(input())
M = []
for i in range(0,n):
    M.append(list(input().split(" ")))
print(matrix_dim(M))
'''
# (b)
'''
def mult_M_v(M,v):
    lst = []
    for i in range(0, len(M)):
        sum = 0
        for j in range(0,len(M[0])):
            sum += int(M[i][j])*int(v[j])
        lst.append([sum])
    return lst
n = int(input())
M = []
for i in range(0,n):
    M.append(list(input().split(" ")))
v = list(input().split(","))
print(mult_M_v(M,v))
'''
# (c)
'''
def transpose(M):
    lst = []
    for i in range(0,len(M[0])):
        temp = []
        for j in range(0,len(M)):
            temp.append(int(M[j][i]))
        lst.append(temp)
    return lst
n = int(input())
M = []
for i in range(0, n):
    M.append(list(input().split(" ")))
print(transpose(M))
'''
# (d)
'''
def largest_col_sum(M):
    max_sum = 0
    for i in range(0,len(M[0])):
        sum = 0
        for j in range(0,len(M)):
            sum += int(M[j][i])
            if sum > max_sum:
                max_sum = sum
    return max_sum
n = int(input())
M = []
for i in range(0, n):
    M.append(list(input().split(" ")))
print(largest_col_sum(M))
'''
# (e)

def switch_columns(M,i,j):
    for p in range(0,len(M)):
        for q in range(0,len(M[0])):
            M[p][q] = int(M[p][q])
    for k in range(0,len(M)):
        temp = M[k][i]
        M[k][i] = M[k][j]
        M[k][j] = temp
    return M
n = int(input())
M = []
for k in range(0, n):
    M.append(list(input().split(" ")))
i = int(input())
j = int(input())
print(switch_columns(M,i,j))
