def IssueCmp(cardNum):
    i = 0
    Len = len(cardNum)
    if Len == 15 and cardNum[i] == '3':
        if cardNum[i+1] == '4' or cardNum[i+1] == '7':
            print("American Express")
    if Len == 16 and cardNum[i] == '5':
        if int(cardNum[i+1]) >= 1 and int(cardNum[i+1]) <= 5:
            print("MasterCard")
    if Len == 13 or Len == 16:
        if cardNum[i] == '4':
            print("Visa")

def validCredit(cardNum):
    longs = len(cardNum)
    i = longs-2
    temp = []
    while i >= 0:
        if cardNum[i] != '0':
            temp.append(int(cardNum[i])*2)
        i -= 2
    sum1 = 0
    for j in temp:
        num = int(j)
        if num >= 10:
            while num > 0:
                sum1 += num % 10
                num //= 10
        else:
            sum1 += num
    i = longs-1
    sum2 = 0
    while i>=0:
        sum2 += int(cardNum[i])
        i -= 2
    sum3 = sum1 + sum2
    if sum3 % 10 == 0:
        print("Valid,", end=' ')
        IssueCmp(cardNum)
    else:
        print("Invalid")


cardNum = input()
validCredit(cardNum)