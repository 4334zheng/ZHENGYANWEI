from math import fabs as f
from math import sqrt

def isValid(side1,side2, side3):
    if side1+side2<=side3 or side1+side3<=side2 or side2+side3<=side1:
        return False
    if f(side1-side2)>=side3 or f(side1-side3)>=side2 or f(side2-side3)>=side1:
        return False
    return True

def perimeter(side1,side2,side3):
    return side1+side2+side3

def area(side1,side2,side3):
    p = (side1+side2+side3)/2
    s = sqrt(p*(p-side1)*(p-side2)*(p-side3))
    return round(s, 3)
