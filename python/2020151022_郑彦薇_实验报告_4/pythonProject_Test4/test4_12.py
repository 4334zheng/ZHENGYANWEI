def generate_triangles():
    sum, num = 0, 1
    while True:
        sum, num = sum + num, num + 1
        yield sum
def generate_triangle_under(N):
    for i in generate_triangles():
        if i > N:
            break
        print(i, end=' ')
if __name__ == '__main__':
    N = int(input())
    generate_triangle_under(N)
