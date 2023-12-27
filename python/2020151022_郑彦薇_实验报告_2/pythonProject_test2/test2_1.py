def emirp(N):
    temp = 13
    list = []
    while N != 0:
        cnt = 0
        i = temp
        num = temp
        for k in range(2, temp):
            if temp%k == 0:
                cnt = 1 #表示是合数，不用进一步判断
                break
        if cnt == 0:
            wei = 0
            while i != 0:
                wei += 1
                i = i//10
            sum = 0
            while wei != 0:
                sum += (temp%10)*(10**(wei-1))
                wei -= 1
                temp = temp//10
            for j in range(2, sum):
                if sum%j == 0:
                    cnt = 1#如果反转是合数，不用输出
                    break
        if cnt == 0 and sum != num:
            N -= 1
            list.append(num)
        temp = num+1

    count = 0
    with open("FirstN_Emirp_Numbers.txt", 'w') as txt:
        for p in list:
            txt.write(str(p) + ' ')
            count += 1
            if count % 10 == 0:
                txt.write('\n')

x = input("Enter the n: ")
N = int(x)
emirp(N)