class Stack(object):
    def __init__(self, content, size, current):
        self.__content = content
        self.__size = size
        self.__current = current
    def isempty(self):
        if self.__current == 0:
            return True
        return False
    def empty(self):
        self.__content.clear()
        self.__current = 0
    def setSize(self, temp):
        self.__size = temp
        while self.__size < self.__current:
            self.pop()
    def isFull(self):
        if self.__current >= self.__size:
            return True
        return False
    def push(self, item):
        if self.isFull():
            print("the stack is full!")
            return
        self.__current += 1
        self.__content.append(item)
    def pop(self):
        if self.isempty():
            print("no items!")
            return
        self.__current -= 1
        self.__content.pop()
    def print_stack(self):
        print(f'当前栈数据个数：{self.__current},当前栈容量：{self.__size}')
        print(self.__content)

'''
S = Stack([], 5, 0)#初始化栈信息：空栈，栈的容量为5，栈当前数据个数为0
S.print_stack()
while 1:#压栈与栈满测试
    item = int(input())
    S.push(item)
    S.print_stack()

S = Stack([0, 1, 2, 3], 5, 4)#初始化栈信息：栈的容量为5，栈当前数据个数为4
cnt = 6#为栈空判断设置测试次数，相当于结束条件
while cnt:#测试出栈与栈空
    S.print_stack()
    S.pop()
    cnt -= 1

S = Stack([0, 1, 2, 3], 5, 4)#初始化栈信息：栈的容量为5，栈当前数据个数为4
S.print_stack()
S.empty()#置空栈测试
S.print_stack()
'''
S = Stack([0, 1, 2, 3], 5, 4)#初始化栈信息：栈的容量为5，栈当前数据个数为4
S.print_stack()
print("请输入新的栈容量：")#设置新的栈容量测试
newSize = int(input())
S.setSize(newSize)
S.print_stack()
