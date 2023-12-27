import re

# 定义DFA状态转移表
state_transition = {
    0: {'letter': 1, 'digit': 2, 'operator': 3, 'delimiter': 4, 'other': 5},
    1: {'letter': 1, 'digit': 1, 'delimiter': 0, 'other': 0},
    2: {'digit': 2, 'dot': 6, 'operator': 0, 'other': 0},
    3: {'operator': 3, 'other': 0},
    4: {'delimiter': 4, 'other': 0},
    5: {'other': 0},
    6: {'digit': 7},
    7: {'digit': 7, 'other': 0}
}
# 定义关键字集合
keywords = {'auto', 'break', 'case', 'char', 'const', 'continue', 'default', 'do', 'double', 'else', 'enum',
            'extern', 'float', 'for', 'goto', 'if', 'int', 'long', 'register', 'return', 'short', 'signed', 'sizeof',
            'static', 'struct', 'switch', 'typedef', 'union', 'unsigned', 'void', 'volatile', 'while'}
# 定义运算符集合
operators = {'+', '-', '*', '/', '%', '=', '>', '<', '!', '&', '|', '^', '~', '++', '--', '+=', '-=', '*=', '/=',
             '%=', '==', '!=', '>=', '<=', '&&', '||', '>>', '<<', '>>=', '<<=', '&=', '|=', '^='}
# 定义分隔符集合
delimiters = {',', ';', '(', ')', '[', ']', '{', '}'}
# 定义注释正则表达式
comment_pattern = re.compile(r'//.*?$|/\*.*?\*/', re.S | re.M)
# 定义空白字符正则表达式
# whitespace_pattern = re.compile(r'\s+')


def tokenize(code):
    # 去除注释
    code = comment_pattern.sub('', code)
    enum_code = enumerate(code)
    # 去除空白字符
    # code = whitespace_pattern.sub('', code)

    # 初始化状态和缓存
    state = 0
    buffer = ''
    tokens = []

    # 遍历代码字符
    for i, c in enumerate(code):
        # 获取字符类型
        if c.isalpha():
            char_type = 'letter'
        elif c.isdigit():
            char_type = 'digit'
        elif c in operators:
            char_type = 'operator'
        elif c in delimiters:
            char_type = 'delimiter'
        else:
            char_type = 'other'

        # 检查状态是否合法
        if char_type not in state_transition[state]:
            # 不合法则回退一个字符
            tokens.append(('不合法', buffer))
            buffer = ''
            state = 0
            continue

        # 更新缓存和状态
        state = state_transition[state][char_type]
        if state != 0:
            buffer += c

        # 检查是否达到终止状态
        if state == 0:
            # 输出Token
            if buffer in keywords:
                tokens.append(('关键字', buffer))
            elif buffer in operators:
                tokens.append(('运算符', buffer))
            elif buffer in delimiters:
                tokens.append(('分隔符', buffer))
            elif re.match(r'^\d+(\.\d+)?$', buffer):
                tokens.append(('整数', buffer))
            elif re.match(r'^[a-zA-Z_]\w*$', buffer):
                tokens.append(('标识符', buffer))
            else:
                tokens.append(('不合法', buffer))
            buffer = ''

    # 检查是否还有未处理的缓存
    if buffer:
        if buffer in keywords:
            tokens.append(('关键字', buffer))
        elif buffer in operators:
            tokens.append(('运算符', buffer))
        elif buffer in delimiters:
            tokens.append(('分隔符', buffer))
        elif re.match(r'^\d+(\.\d+)?$', buffer):
            tokens.append(('整数', buffer))
        elif re.match(r'^[a-zA-Z_]\w*$', buffer):
            tokens.append(('标识符', buffer))
        else:
            tokens.append(('不合法', buffer))

    return tokens

with open('input.c','r',encoding="utf-8") as f:
    code = f.read()
pattern = re.compile(r'[\u4e00-\u9fa5]')
result = pattern.findall(code)
if result:
    print('该文件包含中文')
else:
    tokens = tokenize(code)
    for token in tokens:
        print(token)