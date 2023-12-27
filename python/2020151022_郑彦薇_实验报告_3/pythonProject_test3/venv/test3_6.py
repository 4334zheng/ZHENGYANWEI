def merge(list1, list2):
    List = list1 + list2
    List.sort()
    '''
    len1 = len(list1)
    len2 = len(list2)
    i = j = k = 0
    while i < len1 and j < len2:
        if list1[i] < list2[j]:
            List[k] = list1[i]
            i += 1
            k += 1
        else:
            List[k] = list2[j]
            j += 1
            k += 1
    while i < len1:
        List[k] = list1[i]
        k += 1
        i += 1
    while j < len2:
        List[k] = list2[j]
        k += 1
        j += 1
    '''
    return List

l1 = input()
list1 = [int(n) for n in l1.split()]
List1 = list(list1)
l2 = input()
list2 = [int(n) for n in l2.split()]
List2 = list(list2)
print(merge(List1,List2))