def print_yanghui_triangle(N):
    triangle = [[1]]
    for i in range(2, N+1):
        triangle.append([1] * i)
        for j in range(1, i-1):
            triangle[i-1][j] = triangle[i-2][j-1] + triangle[i-2][j]
    width = len(str(triangle[N-1][len(triangle[N-1])//2])) + 1
    column = len(triangle[N-1]) * width
    for s in triangle:
        res = []
        for c in s:
            res.append('{0:^{1}}'.format(str(c), width))
        print('{0:^{1}}'.format(''.join(res), column))

if __name__ == '__main__':
    N = int(input())
    print_yanghui_triangle(N)

