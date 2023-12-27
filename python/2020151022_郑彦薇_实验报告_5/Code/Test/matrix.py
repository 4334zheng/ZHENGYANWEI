def matrix_dim(M):
    lst = []
    lst.append(len(M))
    lst.append(len(M[0]))
    return lst

def mult_M_v(M,v):
    lst = []
    for i in range(0, len(M)):
        sum = 0
        for j in range(0,len(M[0])):
            sum += int(M[i][j])*int(v[j])
        lst.append([sum])
    return lst

def transpose(M):
    lst = []
    for i in range(0,len(M[0])):
        temp = []
        for j in range(0,len(M)):
            temp.append(int(M[j][i]))
        lst.append(temp)
    return lst

def largest_col_sum(M):
    max_sum = 0
    for i in range(0,len(M[0])):
        sum = 0
        for j in range(0,len(M)):
            sum += int(M[j][i])
            if sum > max_sum:
                max_sum = sum
    return max_sum

def switch_columns(M,i,j):
    for p in range(0,len(M)):
        for q in range(0,len(M[0])):
            M[p][q] = int(M[p][q])
    for k in range(0,len(M)):
        temp = M[k][i]
        M[k][i] = M[k][j]
        M[k][j] = temp
    return M