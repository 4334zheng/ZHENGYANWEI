def is_symmetric(list):
    if list == list[::-1]:
        return True
    return False
def is_almost_symmetric(lst):
    for i in range(0, len(lst)-1):
        for j in range(i+1, len(lst)):
            temp = lst[:]
            temp[i] = lst[j]
            temp[j] = lst[i] #两两交换进行判断
            if is_symmetric(temp):
                return True
    return False
l = input()
lst = [int(n) for n in l.split()]
List = list(lst)
if is_symmetric(List): #对输入的列表进行判断
    print("False")
else:
    if is_almost_symmetric(List):
        print("True")
    else:
        print("False")
