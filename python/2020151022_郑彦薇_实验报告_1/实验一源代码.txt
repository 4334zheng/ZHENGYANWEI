#1

r = input("Enter the radius of a cylinder: ")
h = input("Enter the length of a cylinder: ")
R = float(r)
H = float(h)
area = R*R*3.14159
print("The area is", end=' ')
print(round(area, 4))
volume = area*H
print("The volumn is", end=' ')
print(round(volume, 1))


#2
'''
c = input("Enter number: ")
ch = int(c)
temp = ch
i = 1
sum = 0
while ch//10 != 0:
    i += 1
    ch = ch//10
while i != 0:
    i -= 1
    sum += temp % 10*(10**i)
    temp = temp//10
print(sum)
'''

#3
'''
x = input("Enter an integer: ")
n = int(x)
print("Is", x, "divisible by 5 and 7?", end='')
if (n % 5 == 0) and (n % 7 == 0):
    print("True")
else:
    print("False")
print("Is", x, "divisible by 5 or 7?", end='')
if (n % 5 == 0) or (n % 7 == 0):
    print("True")
else:
    print("False")
print("Is", x, "divisible by 5 or 7,but not both?", end='')
if ((n % 5 == 0) and (n % 7 != 0)) or ((n % 5 != 0) and (n % 7 == 0)):
    print("True")
else:
    print("False")
'''

#4
'''
n = input("Enter the number: ")
temp = int(n)
num = abs(temp)
ch = str()
while num != 0:
    t = num % 7
    ch += str(t)
    num = num // 7
if temp < 0:
    ch += '-'
print(ch[::-1])
'''

#5
'''
x = input("Enter the digit: ")
n = int(x)
cnt = 0
for i in range(10**(n-1),10**n):
    sum = 0
    num = i
    while num != 0:
        sum += (num%10)**n
        num = num//10
    if sum==i:
        cnt = 1
        print(i)
if cnt == 0:
    print("[]")
'''

#6
'''
x = input("Enter the number: ")
i = int(x)
for a in range(1,i+1):
    b = a+1
    sum = a**b
    print(a, b, sum)
'''

#7
'''
x = input("Enter the range: ")
num = int(x)
while num != 0:
    for i in range(2, num):
        if num%i == 0:
            print(num, end='')
            sum = 1
            for k in range(1, num+1):
                sum *= k
            print("!:",sum)
            break
    num -= 1
'''

#8
'''
a = input("Enter the array1: ")
b = input("Enter the array2: ")
x = [int(n) for n in a.split()]
y = [int(n) for n in b.split()]
if len(x) != len(y):
    print("-1")
else:
    sum = 0
    for i in range(0,len(x)):
        sum += x[i]*y[i]
    print(sum)
'''