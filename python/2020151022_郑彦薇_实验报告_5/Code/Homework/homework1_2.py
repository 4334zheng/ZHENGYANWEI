import string
def DealTxt(word):
    for ch in word:
        if ch in string.punctuation or ch == '\n' or '0' <= ch <= '9':
            word = word.replace(ch, " ")
    temp = word.split(' ')
    for i in range(len(temp)-1, -1, -1):
        if temp[i] == '\n' or temp[i] == ' ':
            del temp[i]
            continue
        temp[i] = temp[i].lower()
    return temp

dictword = {}
def getWordNum(filename):
    inputFile=  open(filename, "r")
    while True:
        line = inputFile.readline()
        if not line:
            break
        if line == '\n':
            continue
        wordList = DealTxt(line)
        for temp in wordList:
            if temp in dictword.keys():
                dictword[temp] += 1
            else:
                dictword[temp] = 1
    inputFile.close()

getWordNum('treasure.txt')
getWordNum('hyde.txt')
#getWordNum('war.txt')
res = []
for temp in dictword:
    tuple_temp = (dictword[temp], temp)
    res.append(tuple_temp)
res.sort()
res.reverse()
#print("Leo Tolstoy's Top 20 Words:")
print("Robert Louis Stevenson's Top 20 Words:")
for i in range(1,21):
    print("Frequency: "+str(res[i][0])+" Word: "+str(res[i][1]))