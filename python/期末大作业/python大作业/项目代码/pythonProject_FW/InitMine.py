import data
from block_condition import *


# 不太确定，这里应该就是随机选择4张地图中的一张，然后遍历每一个位置，设定为方块类并获取相应信息
# 根据我们设置好的data获取方块的坐标、周边建筑的数量、方块的状态
class Mine:
    def __init__(self, x, y, value=0):
        self._x = x  # 方块坐标(x,y)，x、y分别为map_data中的i、j
        self._y = y
        self._value = 0  # 0表示方块为数字，1表示方块为建筑
        self._surround_count = -1  # 周边建筑的数量 =>map_data[i][j]
        self._condition = Block_Condition.unclicked  # 初始设置为未点击
        self.set_value(value)

    def get_x(self):
        return self._x

    def set_x(self, x):
        self._x = x

    x = property(fget=get_x, fset=set_x)

    def get_y(self):
        return self._y

    def set_y(self, y):
        self._y = y

    y = property(fget=get_y, fset=set_x)

    def get_value(self):
        return self._value

    def set_value(self, str):
        # 在我们的设定中，是不是建筑就看我们的map_data[i][j]是不是数字集中的数字
        if str in data.number_set:
            self._value = 0  # 不是建筑
        else:
            self._value = 1  # 是建筑

    value = property(fget=get_value, fset=set_value)

    def get_surround_count(self):
        return self._surround_count

    def set_surround_count(self, surround_count):
        self._surround_count = surround_count

    surround_count = property(fget=get_surround_count, fset=set_surround_count)

    # 状态跟鼠标的操作以及方块是否是建筑有关
    def get_condition(self):
        return self._condition

    def set_condition(self, con):
        self._condition = con

    condition = property(fget=get_condition, fset=set_condition)
