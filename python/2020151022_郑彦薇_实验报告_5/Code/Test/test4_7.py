#(1)
print(list(map(lambda x: int(x), ['12', '-2', '0'])))

#(2)
print(list(map(lambda x: len(x), ['hello', 'world'])))

#(3)
print(list(map(lambda x: x[::-1], ['hello', 'world'])))

#(4)
print(list(map(lambda x: (x, x**2, x**3), range(2, 6))))

#(5)
print(list(map(lambda x: x[0] * x[1], zip(range(2, 5), range(3, 9, 2)))))
