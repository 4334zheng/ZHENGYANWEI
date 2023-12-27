def readability(str):
    word_num = len(str.split(' '))
    sent_num = str.count('.') + str.count('!') + str.count('?')
    letter_num = 0
    for i in str:
        if (i <= 'Z' and i >= 'A') or (i <= 'z' and i >= 'a'):
            letter_num += 1
    L = letter_num/word_num*100
    S = sent_num/word_num*100
    index = round(0.0588 * L - 0.296 * S -15.8)
    if index < 1:
        print("Before Grade 1")
    elif index>= 16:
        print("Grade 16+")
    else:
        print(f'Grade {index}')

if __name__ == '__main__':
    str = input()
    readability(str)

