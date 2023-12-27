with open('input.txt', 'r') as f:
    input_str = f.read()

statements = input_str.strip().split(';')
code_str = ''
temp_count = 1
error_list = ['**', '*-', '*+', '*/', '++', '+-', '+*', '+/', '-+', '--', '-*', '-/', '/+', '/-', '/*', '//']


# 定义优先级
def precedence(op):
    if op == '(':
        return 0
    elif op == '+' or op == '-':
        return 1
    elif op == '*' or op == '/':
        return 2
    else:
        return 3

def judge(right):
    # 如果右侧有左括号，看看是否有右括号，如果没有则出错
    if '(' in right and ')' not in right:
        print('括号不匹配，表达式错误！\n')
        return 1

    # 看看运算符是否连续，因为情况较少，所以直接定义一个错误列表进行列举，再看right里面有没有
    for i in error_list:
        if i in right:
            print('运算符连续，表达式错误!\n')
            return 1


for statement in statements:
    parts = statement.strip().split('=')
    left = parts[0].strip()
    right = parts[1].strip().replace(' ', '')
    op_stack = []  # 运算符栈
    val_stack = []  # 变量栈
    temp_var = ''

    if (judge(right) != 1):
        for ch in right:
            if ch.isalpha() or ch.isdigit():
                temp_var += ch
                val_stack.append(temp_var)
            else:
                if ch == '(':
                    op_stack.append(ch)
                elif ch == ')':
                    while op_stack[-1] != '(':
                        # 取出一个简单表达式
                        op = op_stack.pop()
                        val2 = val_stack.pop()
                        val1 = val_stack.pop()
                        temp_var = 't{}'.format(temp_count)
                        temp_count += 1
                        val_stack.append(temp_var)
                        code_str += '{}={}{}{};\n'.format(temp_var, val1, op, val2)
                    op_stack.pop()
                else:
                    while len(op_stack) > 0 and precedence(op_stack[-1]) >= precedence(ch):
                        op = op_stack.pop()
                        val2 = val_stack.pop()
                        val1 = val_stack.pop()
                        temp_var = 't{}'.format(temp_count)
                        temp_count += 1
                        val_stack.append(temp_var)
                        code_str += '{}={}{}{};\n'.format(temp_var, val1, op, val2)
                    op_stack.append(ch)
                temp_var = ''
        # if temp_var != '':
        #     val_stack.append(temp_var)
        while len(op_stack) > 0:
            op = op_stack.pop()
            val2 = val_stack.pop()
            val1 = val_stack.pop()
            temp_var = 't{}'.format(temp_count)
            temp_count += 1
            val_stack.append(temp_var)
            code_str += '{}={}{}{};\n'.format(temp_var, val1, op, val2)
        code_str += '{}={};\n'.format(left, val_stack.pop())
        # if '+' in right or '-' in right or '*' in right or '/' in right:
        #     code_str += 't{}={};\n'.format(temp_count, right)
        #     temp_var = 't{}'.format(temp_count)
        #     temp_count += 1
        # else:
        #     temp_var = right
        # code_str += '{}={};\n'.format(left, temp_var)

with open('output.txt', 'w') as f:
    f.write(code_str)
