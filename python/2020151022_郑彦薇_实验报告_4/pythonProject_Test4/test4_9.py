from functools import reduce

#(1)
print(reduce(max, [23, 49, 6, 32]))

#(2)
print(reduce(lambda x, y: x+y, ['foo', 'bar', 'baz', 'quz']))

#(3)
print(reduce(lambda x, y: x*y, [2, 4, 6]))

