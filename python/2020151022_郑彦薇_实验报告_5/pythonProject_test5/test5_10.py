import collections
import sys
import os

def Collect(myFlie):
    file_num = 0
    code_line = 0
    space_lines = 0
    comments_lines = 0
    for i in os.listdir(myFlie):
        for j in os.listdir(myFlie+'/'+i):
            if j.endswith('.py'):
                file_num += 1
                for line in open(myFlie+'/'+i+'/'+j, encoding='utf-8'):
                    code_line += 1
                    if line == "\n":
                        space_lines += 1
                    if line.startswith('#'):
                        comments_lines += 1
    return(file_num, code_line, space_lines, comments_lines)

def Input_Collect(myFlie):
    file_num = 0
    code_line = 0
    space_lines = 0
    comments_lines = 0
    if not os.path.exists(myFlie):
        print("have no such file!")
        return
    if os.path.isdir(myFlie):
        for i in os.listdir(myFlie):
            for j in os.listdir(myFlie + '/' + i):
                if j.endswith('.py'):
                    file_num += 1
                    for line in open(myFlie + '/' + i + '/' + j, encoding='utf-8'):
                        code_line += 1
                        if line == "\n":
                            space_lines += 1
                        if line.startswith('#'):
                            comments_lines += 1
    elif os.path.isfile(myFlie) and myFlie.endswith('.py'):
        file_num += 1
        for line in open(myFlie, encoding='utf-8'):
            code_line += 1
            if line == '\n':
                space_lines += 1
            if line.startswith('#'):
                comments_lines += 1
    return(file_num, code_line, space_lines, comments_lines)

print("所创建的代码文件夹的信息：")
print(Collect('C:/Users/4334/PycharmProjects/Code'))
print("请正确输入你想统计的文件或文件名地址：")
str = input()
print(Input_Collect(str))