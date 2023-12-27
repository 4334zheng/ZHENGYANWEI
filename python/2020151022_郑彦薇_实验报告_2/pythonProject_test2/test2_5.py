def owlRow(num):
    empty = ' '
    lineA = '     {o,o}'
    lineB = '     /)_) '
    lineC = '      " " '
    for i in range(1, num):
        print(lineA, end='')
    print(lineA)
    for j in range(1, num):
        print(lineB, end='')
    print(lineB)
    for k in range(1, num):
        print(lineC, end='')
    print(lineC)

num = int(input("Enter the num: "))
owlRow(num)