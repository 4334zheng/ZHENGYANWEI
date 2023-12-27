import sys

import pygame

import setting
import time
import random
from InitMine import *
from pygame.locals import *
import tkinter as tk
from tkinter import messagebox, RIGHT, Y, END


class Game(object):
    """游戏类"""

    def __init__(self):
        """初始化"""
        self.prompt_time = 3  # 设置给玩家提供测试次数为3次
        self.try_time = 5  # 设置允许玩家试错次数为5次
        self.game_score = 0  # 分数
        self.game_times = 0  # 时间
        self.win = False  # 未赢
        # 寻找0的递归深度
        self.depth = 2
        # 数字集
        self.num_set = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
        # 屏幕信息初始化
        self.screen_size = setting.screen["size"]
        self.screen_width, self.screen_heigh = self.screen_size
        self.screen_color = setting.screen["color"]
        self.x = 0
        self.y = 0
        self.root = None
        self.scroll = None
        # 字体信息初始化
        self.text_size = setting.text["size"]
        self.text_style = setting.text["style"]
        self.text_color = setting.text["color"]
        self.text_background = setting.text["background"]
        # 标签信息初始化
        self.text_count_pos = setting.lable["count"]
        self.text_time_pos = setting.lable["time"]
        self.text_score_pos = setting.lable["score"]
        self.text_try_pos = setting.lable["try"]
        # 答案选择信息初始化
        self.answers_size = setting.answer["size"]
        self.answers_width, self.answers_height = setting.answer["size"]
        self.answer1_xpos, self.answer1_ypos = setting.answer["answer1_pos"]
        self.answer2_xpos, self.answer2_ypos = setting.answer["answer2_pos"]
        self.answer3_xpos, self.answer3_ypos = setting.answer["answer3_pos"]
        self.answer4_xpos, self.answer4_ypos = setting.answer["answer4_pos"]
        # 地图信息初始化
        self.map_size = setting.map["size"]
        self.map_width, self.map_height = self.map_size
        self.map_color = setting.map["color"]
        self.map_start_point = setting.map["start_point"]
        self.map_block_num = setting.map["block_num"]
        self.map_block_width, self.map_block_height = self.map_block_num
        self.index = random.randint(0, 3)  # 随机获取地图下标
        self.map_data = data.map_data[self.index]  # f这里可以随机选择地图
        # 建筑信息初始化
        self.building_num = data.check_map_data(self.index)
        self.block_num = self.map_block_width * self.map_block_height - self.building_num
        self.block_num_choose = self.block_num
        # 初始化地图状态
        self.map_condition = [[]]
        self.map_condition = [[Mine(x, y, self.map_data[x][y]) for y in range(self.map_block_width)]
                              for x in range(self.map_block_height)]
        for i in range(self.map_block_height):
            for j in range(self.map_block_width):
                if self.map_condition[i][j].value == 0:  # 周边建筑的数量
                    self.map_condition[i][j].surround_count = self.map_data[i][j]
                self.map_condition[i][j].condition = Block_Condition.unclicked
        # 初始化单元格子信息
        self.block_size = setting.block["size"]
        self.block_color = setting.block["color"]
        self.block_dict = {
            0: "pictures/number/0.jpg", 1: "pictures/number/1.jpg", 2: "pictures/number/2.jpg",
            3: "pictures/number/3.jpg", 4: "pictures/number/4.jpg", 5: "pictures/number/5.jpg",
            6: "pictures/number/6.jpg", 7: "pictures/number/7.jpg", 8: "pictures/number/8.jpg",
            9: "pictures/number/9.jpg", 10: "pictures/number/ask.png", 11: "pictures/number/blood.png",
            12: "pictures/number/flag.png", 13: "pictures/number/mine.png"
        }
        pygame.init()  # 使用pygame之前必须初始化
        # 加载图片
        # 答案选项
        self.answer1 = pygame.image.load("pictures/answer/ans1.jpg")
        self.answer1 = pygame.transform.scale(self.answer1, self.answers_size)
        self.answer2 = pygame.image.load("pictures/answer/ans2.jpg")
        self.answer2 = pygame.transform.scale(self.answer2, self.answers_size)
        self.answer3 = pygame.image.load("pictures/answer/ans3.jpg")
        self.answer3 = pygame.transform.scale(self.answer3, self.answers_size)
        self.answer4 = pygame.image.load("pictures/answer/ans4.jpg")
        self.answer4 = pygame.transform.scale(self.answer4, self.answers_size)
        # 单元格子
        self.pictures_dict = {}
        for i in range(14):
            self.pictures_dict[i] = pygame.image.load(self.block_dict[i])  # 加载图片
            self.pictures_dict[i] = pygame.transform.scale(self.pictures_dict[i], self.block_size)  # 设置单元格子大小
        # 初始界面
        self.start_pic = pygame.image.load("pictures/start_pic.jpg")  # 开始游戏部分的界面
        self.start_pic = pygame.transform.scale(self.start_pic, self.screen_size)
        self.start_introduce = pygame.image.load("pictures/start_introduce.jpg")  # 简介部分的界面
        self.start_introduce = pygame.transform.scale(self.start_introduce, self.screen_size)
        self.background = pygame.image.load("pictures/background.jpg")  # 背景图片
        self.background = pygame.transform.scale(self.background, self.screen_size)
        # 可用次数记录、分数记录、时间记录
        self.font = pygame.font.SysFont(self.text_style, self.text_size)  # 字体格式
        self.prom_count = self.font.render("prompt nums：" + str(self.prompt_time), True, self.text_color)
        self.text_use = self.font.render("Try times：" + str(self.try_time), True, self.text_color)
        self.text_score = self.font.render("Score：" + str(self.game_score), True, self.text_color)
        self.text_time = self.font.render("Time：" + str(self.game_times), True, self.text_color)
        self.screen = pygame.display.set_mode(self.screen_size, flags=pygame.RESIZABLE)  # 屏幕主窗口大小、可改变大小
        self.screen.fill(self.screen_color)  # 主窗口背景颜色
        pygame.display.set_caption("py_hw")  # 主窗口标题
        self.screen.blit(self.start_pic, (0, 0))  # 游戏初始界面
        pygame.display.update()

        # 循环，等待查看简介介绍或者直接开始游戏
        pd1, pd2 = True, True  # 加判断，使循环能中断
        while pd1:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                elif event.type == MOUSEBUTTONDOWN:
                    mouse_x, mouse_y = event.pos
                elif event.type == MOUSEBUTTONUP:
                    # 简单地分上下两块，上为开始游戏，下为查看简介
                    if mouse_y < self.screen_heigh / 2:  # 开始游戏
                        pd1 = False
                        break
                    else:  # 显示简介，再次点击则开始游戏
                        self.screen.blit(self.start_introduce, (0, 0))
                        pygame.display.update()
                        while pd2:
                            for tevent in pygame.event.get():
                                if tevent.type == pygame.QUIT:
                                    pygame.quit()
                                    sys.exit()
                                elif tevent.type == MOUSEBUTTONDOWN:
                                    pass
                                elif tevent.type == MOUSEBUTTONUP:
                                    pd1, pd2 = False, False
                                    break
                        break
        self.game_times = time.time()  # 记录开始时间
        self.game_play()  # 开始游戏

    def game_play(self):
        """开始游戏"""
        self.screen.blit(self.background, (0, 0))  # 显示背景
        self.show_blocks()  # 显示地图
        # 标签更新
        self.text_time = self.font.render("时间：" + str(0),
                                          True, self.text_color, self.text_background)
        self.text_score = self.font.render("分数：" + str(self.game_score), True,
                                           self.text_color, self.text_background)
        self.text_use = self.font.render("次数：" + str(self.try_time), True,
                                         self.text_color, self.text_background)
        self.text_prompt = self.font.render("提示：" + str(self.prompt_time), True, self.text_color, self.text_background)
        # 显示标签
        self.screen.blit(self.text_prompt, self.text_count_pos)
        self.screen.blit(self.text_time, self.text_time_pos)
        self.screen.blit(self.text_score, self.text_score_pos)
        self.screen.blit(self.text_use, self.text_try_pos)
        pygame.display.update()
        # 显示答案选项
        self.screen.blit(self.answer1, setting.answer["answer1_pos"])
        self.screen.blit(self.answer2, setting.answer["answer2_pos"])
        self.screen.blit(self.answer3, setting.answer["answer3_pos"])
        self.screen.blit(self.answer4, setting.answer["answer4_pos"])
        # 主循环
        while True:
            self.text_time.fill((0, 0, 0))
            self.text_time = self.font.render("时间：" + str(int(time.time() - self.game_times)) + "s",
                                              True, self.text_color, self.text_background)
            self.screen.blit(self.text_time, self.text_time_pos)
            pygame.display.update()
            # 判断游戏是否结束
            if not self.win and self.block_num_choose <= 0 <= self.try_time:
                self.root = tk.Tk()
                Lable = tk.Label(self.root, text="漂亮，我就知道你能通关！\n想看看有哪些建筑吗？")
                btn1 = tk.Button(self.root)
                btn2 = tk.Button(self.root)
                btn1["text"] = "我一眼就看穿了，不用看了。"
                btn2["text"] = "好啊好啊！愿闻其详！"
                btn1.bind("<Button-1>", self.game_end)
                btn2.bind("<Button-1>", self.show_building)
                Lable.pack()
                btn1.pack()
                btn2.pack()
                self.root.title('Error prompt')
                self.root.geometry("500x300+600+100")
                self.root.mainloop()
            for event in pygame.event.get():  # 监听事件
                if event.type == pygame.QUIT:  # 关闭按钮
                    pygame.quit()  # 卸载所有模块
                    sys.exit()  # 终止程序
                elif event.type == MOUSEBUTTONDOWN:  # 鼠标按下
                    mouse_x, mouse_y = event.pos  # 获取鼠标位置
                    start_x, start_y = self.map_start_point
                    step = self.block_size[0]
                    self.x = (mouse_y - start_y) // step
                    self.y = (mouse_x - start_x) // step
                    b1, b2, b3 = pygame.mouse.get_pressed()  # 鼠标点击的位置
                elif event.type == MOUSEBUTTONUP:  # 鼠标松开
                    # 判断鼠标焦点在地图内
                    if self.map_start_point[0] <= mouse_x <= self.map_start_point[0] + self.map_width and \
                            self.map_start_point[1] <= mouse_y <= self.map_start_point[1] + self.map_height:
                        if b1 and not b3:  # 按鼠标左键
                            if self.map_condition[self.x][self.y].condition == Block_Condition.unclicked:  # 未点击
                                if self.map_condition[self.x][self.y].value == 0:  # 是数字
                                    self.game_score += 10
                                    if self.map_data[self.x][self.y] == 0:  # 是数字0
                                        self.search_zero(self.x, self.y, 0)
                                    else:
                                        self.block_num_choose -= 1
                                        self.map_condition[self.x][self.y].condition = Block_Condition.clicked  # 设置为点击
                                else:  # 是建筑
                                    self.map_condition[self.x][self.y].condition = Block_Condition.bomb  # 设置为碰到建筑
                                    # self.try_time -= 1
                                    # 显示是建筑，弹出错误信息框
                                    self.root = tk.Tk()
                                    # 如果次数用完，弹出弹窗，退出
                                    if self.try_time <= 0:
                                        Lable_end = tk.Label(self.root, text="很抱歉，尝试次数已经用完。")
                                        Lable_end.pack()
                                        btn_end = tk.Button(self.root)
                                        btn_end["text"] = "结束游戏"
                                        btn_end.pack()
                                        btn_end.bind("<Button-1>", self.game_end)
                                    else:
                                        Lable1 = tk.Label(self.root, text='很抱歉，你碰到了地图上的建筑，现在你有两个选择:')
                                        Lable2 = tk.Label(self.root, text='1.我选择继续，并接受试错次数减少一次的代价')
                                        Lable3 = tk.Label(self.root, text='2.我选择查看提示，并接受提示次数减少一次的代价，请告诉我信息吧！')
                                        Lable1.pack()  # pack()用于自动调节组件尺寸
                                        Lable2.pack()
                                        Lable3.pack()
                                        btn1 = tk.Button(self.root)
                                        btn1["text"] = "1.继续游戏"  # 按钮名称
                                        btn1.pack()
                                        btn1.bind("<Button-1>", self.continue_game)
                                        btn2 = tk.Button(self.root)
                                        btn2["text"] = "2.查看提示"
                                        btn2.pack()
                                        btn2.bind("<Button-1>", self.show_answer)
                                    self.root.title('Error prompt')
                                    self.root.geometry("500x200+600+100")
                                    self.root.mainloop()  # 窗口的主事件循环
                            else:  # 已点击
                                pass
                        elif not b1 and b3:  # 按鼠标右键，轮流设置标记
                            if self.map_condition[self.x][self.y].condition == Block_Condition.unclicked:
                                self.map_condition[self.x][self.y].condition = Block_Condition.flag
                            elif self.map_condition[self.x][self.y].condition == Block_Condition.flag:
                                self.map_condition[self.x][self.y].condition = Block_Condition.ask
                            elif self.map_condition[self.x][self.y].condition == Block_Condition.ask:
                                self.map_condition[self.x][self.y].condition = Block_Condition.unclicked
                    # 判断鼠标焦点是否在选项中
                    elif self.answer1_xpos <= mouse_x <= self.answer1_xpos + self.answers_width and \
                            self.answer1_ypos <= mouse_y <= self.answer1_ypos + self.answers_height:
                        self.send_answer(1)
                    elif self.answer2_xpos <= mouse_x <= self.answer2_xpos + self.answers_width and \
                            self.answer2_ypos <= mouse_y <= self.answer2_ypos + self.answers_height:
                        self.send_answer(2)
                    elif self.answer3_xpos <= mouse_x <= self.answer3_xpos + self.answers_width and \
                            self.answer3_ypos <= mouse_y <= self.answer3_ypos + self.answers_height:
                        self.send_answer(3)
                    elif self.answer4_xpos <= mouse_x <= self.answer4_xpos + self.answers_width and \
                            self.answer4_ypos <= mouse_y <= self.answer4_ypos + self.answers_height:
                        self.send_answer(4)
                    else:
                        pass
                    # 更新标签
                    self.text_score = self.font.render("分数：" + str(self.game_score), True,
                                                       self.text_color, self.text_background)
                    self.text_use = self.font.render("次数：" + str(self.try_time), True,
                                                     self.text_color, self.text_background)
                    self.text_prompt = self.font.render("提示：" + str(self.prompt_time), True, self.text_color,
                                                        self.text_background)
                    self.screen.blit(self.text_prompt, self.text_count_pos)
                    self.screen.blit(self.text_score, self.text_score_pos)
                    self.screen.blit(self.text_use, self.text_try_pos)
                    self.show_blocks()  # 显示所有单元格子
                    pygame.display.update()  # 更新屏幕内容(flip更新屏幕内所有内容，update更新改变的内容)

    def show_building(self, event):
        """暂定自己慢慢点开，把尝试次数增加"""
        self.win = True
        self.root.destroy()
        # 添加了滑动条
        self.root = tk.Tk()
        self.scroll = tk.Scrollbar(self.root)
        self.scroll.pack(side=RIGHT, fill=Y)
        mylist = tk.Listbox(self.root, yscrollcommand=self.scroll.set)
        ans = []
        for x in range(self.map_block_height):
            for y in range(self.map_block_width):
                if self.map_data[x][y] not in self.num_set:
                    ans.append("位置({},{})=>{}".format(x, y, self.map_data[x][y]))
        for i in ans:
            mylist.insert(END, i)
        mylist.pack()
        button = tk.Button(self.root, text="好的，明白了！")
        button.bind("<Button-1>", self.game_end)
        button.pack()
        self.root.title('Give answer')
        self.root.geometry("300x210+500+300")
        self.root.mainloop()

    def send_answer(self, pos):
        """判断选择的答案是否正确，回答正确，得分*10，回答错误，尝试次数减3"""
        # 开局未盲猜
        if self.block_num_choose != self.block_num:
            if self.try_time > 3:
                self.root = tk.Tk()
                btn = tk.Button(self.root)
                if self.index == pos - 1:
                    self.game_score *= 10
                    Lable = tk.Label(self.root, text="妙啊！猜对了，你的得分将会翻倍！")
                    Lable.pack()
                    btn["text"] = "无以言表，感激涕零！"
                    btn.pack()
                    btn.bind("<Button-1>", self.game_end)
                else:
                    self.try_time -= 3
                    Lable = tk.Label(self.root, text="有点可惜，你没有蒙对...")
                    Lable.pack()
                    btn["text"] = "下次一定..."
                    btn.pack()
                    btn.bind("<Button-1>", self.pd_answer)
            else:
                self.root = tk.Tk()
                Lable = tk.Label(self.root, text="别点啦！你尝试次数要没啦！")
                btn = tk.Button(self.root)
                btn["text"] = "好的，谢谢提醒！"
                Lable.pack()
                btn.pack()
                btn.bind("<Button-1>", self.pd_answer)
        # 开局盲猜
        else:
            # 提示盲猜后果
            self.root = tk.Tk()
            Lable1 = tk.Label(self.root, text="盲猜可不是个好习惯！\n做个选择吧：\n继续盲猜，对了就赢，错了结束游戏\n取消盲猜，恢复游戏")
            btn1 = tk.Button(self.root)
            btn2 = tk.Button(self.root)
            Lable1.pack()
            btn1["text"] = "我就要盲猜"
            btn2["text"] = "有道理，待会再猜"
            btn1.pack()
            btn2.pack()
            btn1.bind("<Button-1>", self.pd_answer)
            btn2.bind("<Button-1>", self.continue_game)
            self.root.title("Choose")
            self.root.geometry("400x200+500+300")
            self.root.mainloop()
            # 结果判断
            self.root = tk.Tk()
            btn = tk.Button(self.root)
            if self.index == pos - 1:
                Lable = tk.Label(self.root, text="不错不错，蒙对了！\n下局再来！")
                btn["text"] = "运气而已！"
                btn.bind("<Button-1>", self.game_end)
            else:
                Lable = tk.Label(self.root, text="是吧，说了别盲猜！\n你蒙错了！\n重开吧你！")
                btn["text"] = "……"
                btn.bind("<Button-1>", self.game_end)
            Lable.pack()
            btn.pack()
        self.root.title('Give answer')
        self.root.geometry("400x100+500+300")
        self.root.mainloop()

    def pd_answer(self, event):
        self.root.destroy()

    def search_zero(self, x, y, sum):
        """0递归打开"""
        if sum > self.depth:
            return
        self.map_condition[x][y].condition = Block_Condition.clicked
        temp = [False, False, False, False]  # 一二三四象限
        if x - 1 >= 0 and self.map_data[x - 1][y] == 0 and self.map_condition[x - 1][
            y].condition == Block_Condition.unclicked:
            self.search_zero(x - 1, y, sum + 1)
            temp[1], temp[2] = True, True
        if x + 1 < self.map_block_height and self.map_data[x + 1][y] == 0 and self.map_condition[x + 1][
            y].condition == Block_Condition.unclicked:
            self.search_zero(x + 1, y, sum + 1)
            temp[0], temp[3] = True, True
        if y - 1 >= 0 and self.map_data[x][y - 1] == 0 and self.map_condition[x][
            y - 1].condition == Block_Condition.unclicked:
            self.search_zero(x, y - 1, sum + 1)
            temp[2], temp[3] = True, True
        if y + 1 < self.map_block_width and self.map_data[x][y + 1] == 0 and self.map_condition[x][
            y + 1].condition == Block_Condition.unclicked:
            self.search_zero(x, y + 1, sum + 1)
            temp[0], temp[1] = True, True
        if temp[2] and x - 1 >= 0 and y - 1 >= 0 and self.map_data[x - 1][y - 1] == 0 and self.map_condition[x - 1][
            y - 1].condition == Block_Condition.unclicked:
            self.search_zero(x - 1, y - 1, sum + 1)
        if temp[1] and x - 1 >= 0 and y + 1 < self.map_block_width and self.map_data[x - 1][y + 1] == 0 and \
                self.map_condition[x - 1][y + 1].condition == Block_Condition.unclicked:
            self.search_zero(x - 1, y + 1, sum + 1)
        if temp[3] and x + 1 < self.map_block_height and y - 1 >= 0 and self.map_data[x + 1][y - 1] == 0 and \
                self.map_condition[x + 1][y - 1].condition == Block_Condition.unclicked:
            self.search_zero(x + 1, y - 1, sum + 1)
        if temp[0] and x + 1 < self.map_block_height and y + 1 < self.map_block_width and self.map_data[x + 1][
            y + 1] == 0 and self.map_condition[x + 1][y + 1].condition == Block_Condition.unclicked:
            self.search_zero(x + 1, y + 1, sum + 1)
        self.block_num_choose -= 1

    def continue_game(self, event):  # 玩家继续游戏，允许碰到建筑的次数减少一次
        self.try_time -= 1
        self.root.destroy()
        self.game_play()  # 继续游戏

    def show_answer(self, event):  # 玩家点击查看答案，输出原地图图片或者原地图对应矩阵
        self.try_time -= 1
        if self.prompt_time > 0:
            self.prompt_time -= 1
            messagebox.showinfo('提示来啦！',
                                f'你踩中的方块位置为{self.x + 1, self.y + 1}\n这个方块是建筑【{self.map_data[self.x][self.y]}】的一部分噢！')
        else:
            messagebox.showinfo("提示与你擦肩！", "错那么多，不给你提示了！")
        self.root.destroy()

    def game_end(self, event):
        """游戏结束"""
        self.root.destroy()
        self.root = tk.Tk()
        Lable1 = tk.Label(self.root, text="你的用时为：" + str(int(time.time() - self.game_times)) + "s")
        Lable2 = tk.Label(self.root, text="你的得分为：" + str(self.game_score))
        Lable3 = tk.Label(self.root, text="希望这个游戏能帮你更好地了解深大！")
        btn1 = tk.Button(self.root)
        btn1["text"] = "再见了！"
        btn1.bind("<Button-1>", self.pd_answer)
        Lable1.pack()
        Lable2.pack()
        Lable3.pack()
        btn1.pack()
        self.root.title('Error prompt')
        self.root.geometry("500x100+500+300")
        self.root.mainloop()
        self.__init__()

    def show_blocks(self):
        """显示所有单元格子"""
        start_x, start_y = self.map_start_point  # 地图左上角和总屏幕左上角的位置偏移
        width, height = self.map_block_num  # 地图中单元格子的个数
        step_x, step_y = self.block_size  # 单元格子的长宽
        # 遍历显示地图信息
        # 这个部分有点小小的乱，但显示出来是没有问题的
        for x in range(height):
            for y in range(width):
                # 与主窗口左上角位置偏移量
                x_pos = start_y + x * step_x
                y_pos = start_x + y * step_y
                if self.map_condition[x][y].condition == Block_Condition.unclicked:  # 未点击
                    self.screen.blit(self.pictures_dict[9], (y_pos, x_pos))
                elif self.map_condition[x][y].condition == Block_Condition.clicked:  # 点击
                    self.screen.blit(self.pictures_dict[self.map_data[x][y]], (y_pos, x_pos))
                elif self.map_condition[x][y].condition == Block_Condition.mine:  # 建筑
                    self.screen.blit(self.pictures_dict[13], (y_pos, x_pos))
                elif self.map_condition[x][y].condition == Block_Condition.flag:  # 标记为建筑
                    self.screen.blit(self.pictures_dict[12], (y_pos, x_pos))
                elif self.map_condition[x][y].condition == Block_Condition.ask:  # 标记为问号
                    self.screen.blit(self.pictures_dict[10], (y_pos, x_pos))
                elif self.map_condition[x][y].condition == Block_Condition.bomb:  # 碰到建筑
                    self.screen.blit(self.pictures_dict[11], (y_pos, x_pos))


if __name__ == '__main__':
    """测试函数"""
    A = Game()
