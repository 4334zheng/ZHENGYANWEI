from random import choice, randint
print("请输入狐狸可以藏匿的洞口数:", end=' ')
N = int(input())
Maxchoice = 5
print("游戏规则:\n"
      f'(1)狐狸可以藏匿的洞口一共有{N}个,尝试时请勿超出此范围\n'
      f'(2)狐狸会在第二天随机进入今天所在洞口的隔壁洞口,可能是前一个，也可能是后一个\n'
      f'(3)你一共有{Maxchoice}次尝试机会\n'
      f'游戏开始!')
count = 1
fox = randint(1, N+1)
while count <= Maxchoice:
    print("请输入你认为狐狸可能在的洞口位置:", end=' ')
    pos = int(input())
    if pos == fox:
        print(f'恭喜你成功抓住狐狸,你一共用了{count}天')
        break
    if fox == 1:
        fox += 1
    elif fox == N:
        fox -= 1
    else:
        fox += choice((-1, 1))
    count += 1
    if count <= Maxchoice:
        print(f'很遗憾,请第{count}天再来抓')
if count > Maxchoice:
    print("你的尝试次数已用完!失败!")
