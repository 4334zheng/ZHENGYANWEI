def checkSumOfSquareNumbers(c):
    for i in range(1, c):
        for j in range(i, c):
            if i**2+j**2 == c**2:
                return True
    return False

c = int(input("Enter the number: "))
if checkSumOfSquareNumbers(c):
    print("Ture!")
else:
    print("False!")
