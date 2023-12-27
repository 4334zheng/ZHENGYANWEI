class Vertex:
    def __init__(self,name = '',edges = []):
        self.name = name
        self.edges = edges
    def __str__(self):
        return self.name

class Edge:
    def __init__(self,start,end,cost = 1.0):
        self.start = start
        self.end = end
        self.cost = cost
    def __str__(self):
        return str(self.start)

class SimpleGraph:
    def __init__(self,verts = [],edges = []):
        self.verts = verts.copy()
        self.edges = edges.copy()
        self.visit = list()

    def visit_init(self):
        self.visit = [0] * len(self.verts)

    def add_vertex(self,v):
        self.verts.append(v)

    def add_edge(self,e):
        self.edges.append(e)
        for i in self.verts:
            if i == e.start:
                i.edges.append(e.end)
            if i == e.end:
                i.edges.append(e.start)


    def contains_vertex(self,v):
        if v in self.verts:
            return True
        else:
            return False

    def contain_edge(self,e):
        if e in self.edges:
            return True
        else:
            return False

    def get_neighbors(self,v):
        temp = []
        for i,j in v.edges:
            temp.append(j)
        return temp

    def is_empty(self):
        if self.verts == [] and self.edges == []:
            return True
        else:
            return False

    def remove_vertex(self,v):
        self.verts.remove(v)
        for i,j in self.edges:
            if i == v or j == v:
                self.edges.remove((i,j))

    def remove_edge(self,v1,v2):
        self.edges.remove((v1,v2))

    def is_neighbor(self,v1,v2):
        if v2 in v1.edges:
            return True
        else:
            return False

    def find(self,v):
        for i in range(len(self.verts)):
            if self.verts[i] == v:
                return i

    def is_reachable(self,v1,v2):
        self.visit_init()
        f1 = self.find(v1)
        f2 = self.find(v2)
        self.DFS(f1)
        if self.visit[f2] == 1:
            return True
        else:
            return False

    def DFS(self,f1):
        if self.visit[f1] == 1:
            return
        self.visit[f1] = 1
        for i in self.verts[f1].edges:
            f = self.find(i)
            self.DFS(f)

    def clear_all(self):
        self.verts = []
        self.edges = []

    def show(self):
        print("verts: ",end="")
        print(list(x.name for x in self.verts))
        print("edges: ",end="")
        print(list((x.start.name,x.end.name) for x in self.edges))
a = Vertex("aa")
b = Vertex("bb")
print(a)
print(b)
edge1 = Edge(a,b)
verts = [a,b]
edges = [edge1]
my_graph = SimpleGraph()
my_graph.show()
my_graph.add_vertex(a)
my_graph.add_vertex(b)
my_graph.show()
print(my_graph.is_reachable(a,b))
my_graph.add_edge(edge1)
my_graph.show()
print(my_graph.is_reachable(a,b))

