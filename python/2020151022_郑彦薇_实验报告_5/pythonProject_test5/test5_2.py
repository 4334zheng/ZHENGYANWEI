import math
class RegularPolygon(object):
    def __init__(self, n=3, side=1, x=0, y=0):
        self.__n = n
        self.__side = side
        self.__x = x
        self.__y = y
    def getPerimeter(self):
        return self.__side * self.__n
    def getArea(self):
        return 0.25 * self.__n * (self.__side) ** 2 / math.tan(math.pi / self.__n)
    def distanceToPolygon(self, Rp):
        return math.sqrt((self.__x - Rp.__x) ** 2 + (self.__y - Rp.__y) ** 2)

print("请输入正n边形的信息：")
n1 = int(input())
side1 = float(input())
x1 = float(input())
y1 = float(input())
Rp1 = RegularPolygon(n1, side1, x1, y1)
print(f'C = {Rp1.getPerimeter()}')
print(f'S = {round(Rp1.getArea(), 4)}')
print("请输入另一个正n边形的信息：")
n2 = int(input())
side2 = float(input())
x2 = float(input())
y2 = float(input())
Rp2 = RegularPolygon(n2, side2, x2, y2)
print(f'D = {round(Rp1.distanceToPolygon(Rp2), 4)}')
