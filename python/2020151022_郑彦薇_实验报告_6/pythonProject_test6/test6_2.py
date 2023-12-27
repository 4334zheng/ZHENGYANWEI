from tkinter import *
from tkinter import messagebox
class Circle:
    def __init__(self):
        root = Tk()
        root.title("Circle")
        label = Label(root, text="drag circles to get dis")
        label.pack()
        self.canvas = Canvas(root, width=500, height=300)  # 添加画布
        self.canvas.pack()
        # 初始化两个圆的位置
        self.x1 = 100
        self.y1 = 100
        self.x2 = 200
        self.y2 = 200
        self.r = 20
        self.display_ele()
        self.canvas.bind("<B1-Motion>", self.MyMouse)
        root.mainloop()

    def get_dis(self):
        return ((self.x1 - self.x2)**2 + (self.y1 - self.y2)**2)
    def display_ele(self):
        self.canvas.delete('all')
        # 画布上显示两个圆
        self.canvas.create_oval(self.x1-self.r, self.y1-self.r, self.x1+self.r, self.y1+self.r, fill='red',
                                outline="black", tag='circle1')
        self.canvas.create_oval(self.x2-self.r, self.y2-self.r, self.x2 + self.r, self.y2 + self.r, fill='red',
                                outline="black", tag='circle2')
        # 两圆圆心确定一条直线
        self.canvas.create_line(self.x1, self.y1, self.x2, self.y2)
        # 线上显示两圆距离，距离在线上显示
        self.canvas.create_text((self.x1+self.x2)/2, (self.y1+self.y2)/2, text="{:.2f}".format(self.get_dis()))
    def Dealcoincide(self):
        # 显示错误信息框
        messagebox.showinfo("Error!", "Forbidden Coincide!")
        # 恢复初始状态
        self.x1 = 100
        self.y1 = 100
        self.x2 = 200
        self.y2 = 200
        self.display_ele()
    # 监听鼠标
    def MyMouse(self, event):
        newX, newY = event.x, event.y
        # 圆1被移动
        if self.x1 - self.r < newX < self.x1 + self.r and self.y1 - self.r < newY < self.y1 + self.r:
            if self.get_dis() == 0:  # 如果两圆重合
                self.Dealcoincide()
                return
            # 圆没有重合，更新圆的新位置并进行展示
            self.x1 = newX
            self.y1 = newY
            self.display_ele()
        # 圆2被移动
        elif self.x2 - self.r < newX < self.x2 + self.r and self.y2 - self.r < newY < self.y2 + self.r:
            if self.get_dis() == 0:  # 如果两圆重合
                self.Dealcoincide()
                return
            # 圆没有重合，更新圆的新位置并进行展示
            self.x2 = newX
            self.y2 = newY
            self.display_ele()

Test = Circle()
Test