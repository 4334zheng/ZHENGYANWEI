def match_pattern(list1, list2):
    len1 = len(list1)
    len2 = len(list2)
    i = j = 0
    while j < len1:
        if list2[i] == list1[j]:
            i += 1
            j += 1
            while i < len2 and j < len1:
                if list2[i] != list1[j]:
                    return False
                i += 1
                j += 1
            if i == len2:
                return True
        j += 1
    return False

l1 = input()
list1 = [int(n) for n in l1.split()]
List1 = list(list1)
l2 = input()
list2 = [int(n) for n in l2.split()]
List2 = list(list2)
if match_pattern(List1,List2):
    print("True")
else:
    print("False")