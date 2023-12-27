def Divide_cookies(list1,list2):
    list1.sort() #对贪吃指数排序
    list2.sort() #对饼干尺寸排序
    i = count = 0
    for j in list2: #遍历每一块饼干
        if j >= list1[i]: #如果饼干大于贪吃指数
            count += 1 #得到满足的孩子个数+1
            i += 1 #换下一个小朋友进行判断
        if i >= len(list1):
            break; #如果每一个小朋友都遍历，则结束分饼干
    return count
l1 = input()
list1 = [int(n) for n in l1.split()]
List1 = list(list1)
l2 = input()
list2 = [int(n) for n in l2.split()]
List2 = list(list2)
print(Divide_cookies(List1,List2))