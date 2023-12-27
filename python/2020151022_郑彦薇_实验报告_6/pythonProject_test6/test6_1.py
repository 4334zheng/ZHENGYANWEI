from tkinter import *
import random
def randomcolor():#让python随机生成颜色方法
    colorArr = ['1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
    color = ""
    for i in range(6):
        color += colorArr[random.randint(0, 14)]
    return '#' + color

def display():
    canvas.delete('all')#清空画布
    for i in range(10):
        x = random.randint(50, 450)
        y = random.randint(50, 250)#随机生成球的位置坐标
        R = 10#设定半径
        color = randomcolor()#获取随机颜色
        canvas.create_oval(x, y, x+R, y+R, fill=color, outline="black")

root = Tk()
root.title('Random Balls')
label = Label(root, text="click button to get balls")
label.pack()
canvas = Canvas(root, width=500, height=300)#添加画布
canvas.pack()
button = Button(root, text='Display', command=display)
button.pack()
root.mainloop()