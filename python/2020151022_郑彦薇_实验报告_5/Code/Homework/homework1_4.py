def Judgeinput1(str):
    if len(str) != 5:
        print("错误!数字长度必须是5!", end=' ')
        return False
    for i in range(len(str)-1):
        for j in range(i+1, len(str)):
            if str[i] == str[j]:
                print("错误!不能重复数字!", end=' ')
                return False
    return True

def Judgeinput2(str):
    for i in range(len(str)):
        if str[i] < '0' or str[i] > '9':
            print("错误!只允许使用数字!", end=' ')
            return False
    return True

def Guess(str1, str2):
    wei = 0
    pos = 0
    for i in range(len(str1)):
        for j in range(len(str2)):
            if str1[i] == str2[j]:
                wei += 1
    for i in range(len(str1)):
        if str1[i] == str2[i]:
            pos += 1
    if wei == 5 and pos == 5:
        print("成功!!!你一共猜了", end='')
        return True
    print(f'正确位数{wei}, 正确位置位数{pos}')


print("请输入原始数字:", end=' ')
str1 = list(input())
while Judgeinput1(str1) != True:
    print("重新输入:", end=' ')
    str1 = list(input())
Maxcount = 5
print(f"游戏规则:\n(1)输入数字格式错误不计次数!\n"
      f"(2)输入EXIT可以结束游戏,视为游戏失败!\n"
      f"(3)你只有{Maxcount}次机会!\n"
      f"游戏开始!")
count = 1
while count <= Maxcount:
    print("请输入你猜的数: ", end=' ')
    str2 = list(input())
    temp = ''.join(str2)
    if temp == 'EXIT':
        print(f'你已提前退出游戏,游戏失败,你一共猜了{count-1}次!')
        break
    while Judgeinput2(str2) != True or Judgeinput1(str2) != True:
        print("再猜一次:", end=' ')
        str2 = list(input())
        temp = ''.join(str2)
    print(f'猜测次数{count}, 猜测数字{temp},', end=' ')
    if Guess(str1, str2) == True:
        print(f'{count}次')
        break
    count += 1
if count > Maxcount:
    print("达到猜测上限!失败!!!")
