import Triangle

side1 = int(input())
side2 = int(input())
side3 = int(input())
if Triangle.isValid(side1, side2, side3):
    print("True!")
else:
    print("False!")

side1 = int(input())
side2 = int(input())
side3 = int(input())
print(Triangle.perimeter(side1, side2, side3))

side1 = int(input())
side2 = int(input())
side3 = int(input())
print(Triangle.area(side1, side2, side3))