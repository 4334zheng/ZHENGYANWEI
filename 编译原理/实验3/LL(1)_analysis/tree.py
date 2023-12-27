# from pygram import Grammar
# from prettytable import PrettyTable
# g = Grammar()
# g.add_terminals('id', '+', '*', '(', ')')
# g.add_nonterminals('E', 'T', 'F')
# g.set_start('E')
# g.add_rules({
#     'E': ['T', 'E + T'],
#     'T': ['F', 'T * F'],
#     'F': ['( E )', 'id']
# })

class Node:
    def __init__(self, label, children=None):
        self.label = label
        self.children = children or []
    def __str__(self):
        if not self.children:
            return self.label
        return f"({self.label} {' '.join(str(c) for c in self.children)})"
def parse(predict_table, start_symbol, input_str, epsilon=None):
    stack = ['$S']
    input_str += '$'
    i = 0
    while len(stack) > 0 and i < len(input_str):
        top = stack[-1]
        a = input_str[i]
        if top == a:
            stack.pop()
            i += 1
        elif top in predict_table and a in predict_table[top]:
            productions = predict_table[top][a]
            if len(productions) > 0:
                stack.pop()
                for symbol in reversed(productions[0].right):
                    stack.append(symbol)
                if productions[0].right[0] != epsilon:
                    node = Node(productions[0].left, [])
                    for _ in range(len(productions[0].right)):
                        node.children.append(Node(stack.pop(), []))
                    stack.append(node)
                else:
                    stack.append(Node(productions[0].left, []))
            else:
                raise SyntaxError(f"Unexpected token: {a}")
        else:
            raise SyntaxError(f"Unexpected token: {a}")
    return stack[0]

def construct_predict_table(grammar):
    predict_table = {}
    nonterminals = grammar.get_nonterminals()
    terminals = grammar.get_terminals()
    start_symbol = grammar.get_start_symbol()
    # 初始化分析表
    for A in nonterminals:
        predict_table[A] = {}
        for a in terminals:
            predict_table[A][a] = []
    # 处理每个产生式
    for production in grammar.get_productions():
        A = production.left
        alpha = production.right
        first_alpha = grammar.first(alpha)
        follow_A = grammar.follow(A)
        for a in first_alpha:
            if a != grammar.epsilon:
                predict_table[A][a].append(production)
        if grammar.epsilon in first_alpha:
            for b in follow_A:
                predict_table[A][b].append(production)
    return predict_table, start_symbol

# predict_table ,start_symbol = construct_predict_table(g)

# terminals = g.get_terminals()
# terminals.append('$')  # 加入结束符号
# table = PrettyTable([''] + terminals)
# for A in g.get_nonterminals():
#     row = [A]
#     for a in terminals:
#         row.append(' '.join(str(p) for p in predict_table[A][a]))
#     table.add_row(row)
# print(table)

predict_table = {
    'E': {'(': ('E', 'T)'), 'NUM': ('E\'', 'T', 'E\'')},
    'E\'': {'+': ('+', 'T', 'E\''), '-': ('-', 'T', 'E\''), ')': ('ε',)},
    'T': {'(': ('T', 'F)'), 'NUM': ('T\'', 'F', 'T\'')},
    'T\'': {'*': ('*', 'F', 'T\''), '/': ('/', 'F', 'T\''), '+': ('ε',), '-': ('ε',), ')': ('ε',)},
    'F': {'(': ('(', 'E', ')'), 'NUM': ('NUM',)}
}
start_symbol = 'E'
root = parse(predict_table, start_symbol, '2+3*(4-1')
print(root)