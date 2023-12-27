from math import gcd
from functools import reduce
def lcm(*nums):
    print(int(reduce(lambda x, y: x*y/gcd(int(x), int(y)), nums, 1)))

if __name__ == '__main__':
    lcm(3, 5)
    lcm(41, 106, 12)
    lcm(1, 2, 6, 24, 120, 720)
    lcm(3)
    lcm()

