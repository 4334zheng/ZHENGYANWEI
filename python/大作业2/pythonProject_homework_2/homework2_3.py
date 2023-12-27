import random

class Vertex():
    def __init__(self, name, edges=[]):
        self.name = name
        self.edges = edges

class Edge(Vertex):
    def __init__(self, start, end, cost=1.0):
        self.start = start
        self.end = end
        self.cost = cost

class SimpleGraph(Edge):
    def __init__(self, verts=[], edges=[]):
        self.verts = verts
        self.edges = edges
        self.visit = [0] * len(verts)#访问数组，长度与顶点列表长度相同，在dfs中使用

    def add_vertex(self, v):
        self.verts.append(v) #列表直接添加顶点元素

    def add_edge(self, v1, v2):
        e = Edge(v1, v2, 1.0)
        self.edges.append(e)
        for i in self.verts:#创建邻接表
            if e.start.name == i.name:
                i.edges.append(e.end)

    def contains_vertex(self, v):
        for i in self.verts: # 遍历顶点列表，查看是否存在顶点v
            if i.name == v:
                return True
        return False

    def contains_edge(self, v1, v2):
        for e in self.edges: # 遍历边列表
            if e.start.name == v1 and e.end.name == v2:
                return True
        return False

    def get_neighbors(self, v):
        temp = [] # 记录v的邻居
        for i in self.edges:
            if i.start.name == v:
                temp.append(i.end.name)
        return temp

    def is_empty(self):
        # 顶点列表、边列表都为空
        if len(self.verts) == 0 and len(self.edges) == 0:
            print("the graph is empty!")
            return
        print("there are still info didn't be clear!")

    def remove_vertex(self, v):
        for i in self.edges:
            if i.start.name == v or i.end.name == v:
                self.edges.remove(i)
        for vex in self.verts:
            if vex.name == v:
                self.verts.remove(vex)# 删除顶点v

    def remove_edge(self, v1, v2):
        for i in self.verts:
            if i.name == v1:
                for j in i.edges:
                    if j.name == v2:
                        i.edges.remove(j)
        for e in self.edges:
            if e.start.name == v1 and e.end.name == v2:
                self.edges.remove(e)

    def is_neighbor(self, v1, v2):
        for i in self.edges:
            if i.start.name == v1 and i.end.name == v2:
                return True
        return False

    def index(self, v):
        for i in range(len(self.verts)):
            if self.verts[i].name == v:
                return i

    def is_reachable(self, v1, v2):
        # 判断是否存在路径可以由顶点 v1 到达顶点 v2,使用dfs求解
        self.VisitInit()
        index1 = self.index(v1)
        index2 = self.index(v2)
        self.DFS(index1)
        if self.visit[index2] == 1:
            return True
        return False

    def VisitInit(self):
        self.visit = [0] * len(self.verts)

    def DFS(self, i):
        if self.visit[i] == 1:
            return
        self.visit[i] = 1
        for j in self.verts[i].edges:
            d = self.index(j.name)
            self.DFS(d)

    def clear_all(self):# 清空图，删除所有顶点和所有边
        self.edges.clear()
        self.verts.clear()

    def print(self):
        if len(self.verts) == 0 and len(self.edges) == 0:
            print("the graph is empty!")
            return
        temp = []
        for v in self.verts:
            temp.append(v.name)
        print(f'顶点列表：{temp}')
        temp = []
        for v in self.edges:
            temp.append((v.start.name, v.end.name))
        print(f'边列表：{temp}')

def test():
    # 创建图信息
    #vex = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    #edge = [('0', '1'), ('1', '2'), ('1', '3'), ('0', '4'), ('1', '5'), ('2', '6'), ('4', '7'), ('3', '6'), ('5', '9'), ('7', '9')]

    MyGraph = SimpleGraph()
    #MyGraph.print()
    # 测试图的功能函数
    print("测试功能1--添加顶点")
    #往图中添加10个点
    MyGraph.add_vertex(Vertex('0'))
    MyGraph.add_vertex(Vertex('1'))
    MyGraph.add_vertex(Vertex('2'))
    MyGraph.add_vertex(Vertex('3'))
    MyGraph.add_vertex(Vertex('4'))
    MyGraph.add_vertex(Vertex('5'))
    MyGraph.add_vertex(Vertex('6'))
    MyGraph.add_vertex(Vertex('7'))
    MyGraph.add_vertex(Vertex('8'))
    MyGraph.add_vertex(Vertex('9'))
    print("当前图信息：")
    MyGraph.print()
    print("测试功能2--添加边")
    MyGraph.add_edge(Vertex('0'), Vertex('1'))
    MyGraph.add_edge(Vertex('1'), Vertex('2'))
    MyGraph.add_edge(Vertex('1'), Vertex('3'))
    MyGraph.add_edge(Vertex('0'), Vertex('4'))
    MyGraph.add_edge(Vertex('1'), Vertex('5'))
    MyGraph.add_edge(Vertex('2'), Vertex('6'))
    MyGraph.add_edge(Vertex('4'), Vertex('7'))
    MyGraph.add_edge(Vertex('3'), Vertex('6'))
    MyGraph.add_edge(Vertex('5'), Vertex('9'))
    MyGraph.add_edge(Vertex('7'), Vertex('9'))
    print("当前图信息：")
    MyGraph.print()
    print("现在你拥有一张图，开始测试其他函数功能！")
    print("测试功能3--判断图中是否存在顶点v")
    if MyGraph.contains_vertex('0'):
        print(f'顶点0在图中')
    else:
        print(f'顶点0不在图中')
    print("测试功能4--判断图中是否存在边(v1,v2)")
    if MyGraph.contains_edge('0', '1'):
        print(f'边(0, 1)在图中')
    else:
        print(f'边(0, 1)不在图中')
    print("测试功能5--获得顶点v的邻居")
    print(f'1的邻居有{MyGraph.get_neighbors("1")}')
    print("测试功能6--判断图是否为空")
    MyGraph.is_empty()
    print("测试功能7--删除顶点v")
    MyGraph.remove_vertex('0')
    print(f'删除顶点0后的图信息为：')
    MyGraph.print()
    print("测试功能8--删除边(v1,v2)")
    MyGraph.remove_edge('1', '2')
    print(f'删除边(1, 2)后的图信息为：')
    MyGraph.print()
    print("测试功能9--判断顶点v2是否为v1的邻居")
    if MyGraph.is_neighbor('1', '3'):
        print(f'顶点3是1的邻居')
    else:
        print(f'顶点3不是1的邻居')
    print("测试功能10--判断是否存在路径可以由顶点v1到达顶点v2")
    if MyGraph.is_reachable('1', '9'):
        print(f'存在路径由1到达9')
    else:
        print(f'不存在路径由1到达9')
    print("测试功能11--删除所有顶点和边")
    MyGraph.clear_all()
    print("删除所有顶点和边后再次测试功能6--判断图是否为空，同时验证clear_all正确性")
    MyGraph.is_empty()

test()