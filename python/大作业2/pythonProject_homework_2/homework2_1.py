class SM:
    def __init__(self):
        self.start_state = None
    def transition_fn(self, s, x):#在子类中实现
        pass
    def output_fn(self, s):#在子类中实现
        pass
    def transduce(self, input_seq):
        for i in range(len(input_seq)):
            self.start_state = self.transition_fn(self, self.start_state, input_seq[i])
        print(self.output_fn(self, self.start_state))

class Accumulator(SM):
    start_state = 0
    def transition_fn(self, s, x):
        return s + x
    def output_fn(self, s):
        return s

class Binary_Addition(SM):
    start_state = (0, [])
    def transition_fn(self, s, x):
        temp = s[1]
        if s[0] + x[0] + x[1] == 3:
            temp.append(1)
            s = (1, temp)
        elif s[0] + x[0] + x[1] == 2:
            temp.append(0)
            s = (1, temp)
        elif s[0] + x[0] + x[1] == 1:
            temp.append(1)
            s = (0, temp)
        else:
            temp.append(0)
            s = (0, temp)
        return s
    def output_fn(self, s):
        if s[0] == 1:
            s[1].append(1)
        return s[1]

class Reverser(SM):
    start_state = (0, 0, 0, [])
    def transition_fn(self, s, x):
        temp = s[3]
        temp.append(x)
        if s[0] == 1:
            return 1, s[1], s[2] + 1, temp
        if x == 'end':
            return 1, s[1], s[2] + 1, temp
        else:
            return 0, s[1] + 1, s[2] + 1, temp
    def output_fn(self, s):
        res = []
        for i in range(s[2]):
            if i < s[1]:
                res.append(None)
            elif s[1] <= i <= 2*s[1]-1:
                res.append(s[3][2*s[1]-1-i])
            else:
                res.append(None)
        return res

print("Accumulator:")
A = Accumulator
A.transduce(A, [-1, 2, 3, -2, 5, 6])
print("Binary_Addition:")
B = Binary_Addition
B.transduce(B, [(1, 1), (1, 0), (0, 0)])
print("Reverser:")
R = Reverser
R.transduce(R, list('nehznehS evol I') + ['end'] + list(range(15)))