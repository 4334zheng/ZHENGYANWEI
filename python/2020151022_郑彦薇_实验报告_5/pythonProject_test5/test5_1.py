#(a)
print("问题a的结果：")
class Clock(object):
    def __init__(self,time):
        self.time = time
    def print_time(self):
        time = "6:30"
        print(self.time)

clock = Clock("5:30")
clock.print_time()

#(b)
print("问题b的结果：")
class Clock(object):
    def __init__(self,time):
        self.time = time
    def print_time(self,time):
        print(time)
clock = Clock("5:30")
clock.print_time("10:30")

#(c)
print("问题c的结果：")
class Clock(object):
    def __init__(self,time):
        self.time = time
    def print_time(self):
        print(self.time)
boston_clock = Clock("5:30")
paris_clock = boston_clock
paris_clock.time = "10:30"
boston_clock.print_time()
paris_clock.print_time()