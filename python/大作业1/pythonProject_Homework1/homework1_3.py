def offByOne(str1, str2):
    l1 = len(str1)
    l2 = len(str2)
    if l1 != l2:
        return False
    count = 0
    for i in range(l1):
        if str1[i] != str2[i]:
            count += 1
    if count != 1:
        return False
    return True

def offBySwap(str1, str2):
    if len(str1) == len(str2) and str1 != str2:
        for i in range(len(str1)-1):
            temp = str1[:]
            temp[i] = str1[i+1]
            temp[i+1] = str1[i]
            if temp == str2:
                return True
    return False

def offByExtra(str1, str2):
    l1 = len(str1)
    l2 = len(str2)
    if l1 == l2+1:
        for i in range(l1):
            temp1 = str1[:]
            temp1.pop(i)
            if temp1 == str2:
                return True
    if l2 == l1+1:
        for i in range(l2):
            temp2 = str2[:]
            temp2.pop(i)
            if temp2 == str1:
                return True
    return False

def getWords(filepath):
    file = open(filepath)
    wordOne = []
    while file:
        line = file.readline()
        word = line.split(' ')
        wordOne.extend(word)
        if not line:
            break
    wordTwo = []
    for i in wordOne:
        wordTwo.extend(i.split())
    return wordTwo

def ListOfNeighbors(str, L):
    res = []
    for i in range(len(L)):
        if offByExtra(str, list(L[i])) or offByOne(str, list(L[i])) or offBySwap(str, list(L[i])):
            res.append(L[i])
    for j in range(len(res)):
        print(res[j], end=' ')

str = input()
s = list(str)
filepath = 'EnglishWords.txt'
L = getWords(filepath)
ListOfNeighbors(s,L)

#str1 = input()
#str2 = input()
#s1 = list(str1)
#s2 = list(str2)

#if offBySwap(s1, s2):
#if offByExtra(s1, s2):
#    print("True")
#else:
#    print("False")

#if offByOne(str1, str2):
#    print("True")
#else:
#    print("False")
