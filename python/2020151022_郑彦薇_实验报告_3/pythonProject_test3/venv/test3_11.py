import string
#去除文本中的符号，将它们转换为空格
def removePunctuations(word):
    for ch in word:
        if ch in string.punctuation:
            word = word.replace(ch," ")
    return word
#以文本中的空格和换行符将单词分划出来，得到一个只存放了单词的列表
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
#统计每个关键字在文本nARQ出现的次数，并计算总数
def getWordNum(words):
    dictword = {"and":0, "as":0, "assert":0, "break":0, "class":0,
                "continue":0, "def":0, "del":0, "elif":0, "else":0,
                "except":0, "False":0, "finally":0, "for":0, "from":0,
                "global":0, "if":0, "import":0, "in":0, "is":0, "lambda":0,
                "None":0, "nonlocal":0, "not":0, "or":0, "pass":0, "raise":0,
                "return":0, "True":0, "try":0, "while":0, "with":0, "yield":0}
    for i in words:
        if i in dictword:
            dictword[i] += 1
    for key, value in dictword.items():
        print(f'nARQ中{key}出现：{value}次')
    sum = 0
    for value in dictword.values():
        sum += value
    print(f'nARQ文件中关键字共出现：{sum}次')

filepath = 'nARQ.txt'
file = removePunctuations(filepath)
words = getWords(filepath)
getWordNum(words)