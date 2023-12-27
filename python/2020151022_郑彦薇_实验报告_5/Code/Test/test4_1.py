def find1(s, t):
    temp = s.find(t)
    if temp == -1:
        return False
    return True
def find2(s, t):
    s1 = list(s)
    t1 = list(t)
    l1 = len(s1)
    l2 = len(t1)
    j = 0
    for i in range(l1):
        if t[j] == s[i]:
            j += 1
        if j == l2:
            return True
    return False
s = input()
t = input()
if find2(s, t):
#if find1(s, t):
    print("True")
else:
    print("False")
