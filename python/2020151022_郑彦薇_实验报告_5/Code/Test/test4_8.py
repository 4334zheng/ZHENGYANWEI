#(1)
print(list(filter(lambda x: x > '0', ['12', '-1', '0'])))

#(2)
print(list(filter(lambda x: x[0] == 'w', ['hello', 'world'])))

#(3)
print(list(filter(lambda x: x[0:4:1] == 'tech', ['technology', 'method', 'technique'])))

#(4)
print(list(filter(lambda x: x % 3 == 0 or x % 5 == 0, range(0, 20))))

