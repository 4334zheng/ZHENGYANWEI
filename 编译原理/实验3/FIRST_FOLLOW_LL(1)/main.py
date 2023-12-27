'''
# 定义文法的产生式
productions = {
    'E': ['E+T', 'T'],
    'T': ['int', 'float', 'double', 'long'],
    'B': ['B and U', 'U'],
    'U': ['true', 'false'],
    'V': ['var'],
    'A': ['V=E', 'B'],
    'C': ['if (B) L else L'],
    'S': ['A', 'C'],
    'L': ['S;L', 'S'],
    'P': ['L']
}
# 求解各个非终结符的First集合
def first_set(productions):
    first = {}
    for key in productions:
        first[key] = set()  # 初始化First集为空集
    while True:
        updated = False  # 用于标记是否有First集更新
        for key in productions:
            for production in productions[key]:
                if production[0] not in first[key]:  # 如果第一个符号不在First集中
                    if production[0] not in productions.keys():  # 如果第一个符号是终结符
                        first[key].add(production[0])  # 将该符号加入First集中
                        updated = True  # 标记First集更新
                    else:  # 如果第一个符号是非终结符
                        for symbol in production:  # 遍历产生式中的符号
                            if symbol in first.keys():  # 如果符号的First集已求出
                                first[key] |= first[symbol]  # 将该符号的First集加入当前符号的First集中
                                if 'ε' not in first[symbol]:  # 如果该符号的First集中没有空串，跳出循环
                                    break
                            else:  # 如果符号的First集还没求出
                                first[key].add(symbol)  # 将该符号加入到当前符号的First集合中
                                break  # 跳出循环
                        else:  # 如果产生式中的符号所有的First集合都包含空串
                            first[key].add('ε')  # 将空串加入到当前符号的First集合中
                            updated = True  # 标记First集更新
        if not updated:  # 如果所有非终结符的First集都已求出，跳出循环
            break
    return first
# 求解各个非终结符的Follow集合
def follow_set(productions, first):
    follow = {}
    for key in productions:
        follow[key] = set()
    follow['P'].add('$')
    while True:
        updated = False
        # 遍历每个非终结符的每个产生式
        for key in productions:
            for production in productions[key]:
                # 遍历产生式中的每个符号
                for i, symbol in enumerate(production):
                    # 如果当前符号是一个非终结符号
                    if symbol in productions.keys():
                        if i == len(production) - 1:  # 最后一个符号
                            follow[symbol] |= follow[key]
                        else:
                            for j in range(i+1, len(production)):
                                if production[j] in first.keys():
                                    follow[symbol] |= first[production[j]]
                                    # 如果该符号的First集不包含空串，则跳出循环
                                    if 'ε' not in first[production[j]]:
                                        break
                                else:
                                    # 如果该符号是终结符号，则将其加入该非终结符的Follow集
                                    follow[symbol].add(production[j])
                                    break
                            else:
                                # 如果符号后面的所有符号的First集都包含空串，则将该非终结符的Follow集加上该非终结符所在产生式所在非终结符的Follow集
                                follow[symbol] |= follow[key]
        if not updated:
            break
    return follow
# 将文法转化为LL(1)文法
def ll1_grammar(productions, first, follow):
    ll1_productions = {}
    for key in productions:
        ll1_productions[key] = []
    for key in productions:
        for production in productions[key]:
            new_production = []
            for symbol in production.split(' '):
                if symbol in productions.keys():
                    new_production += list(first[symbol] - {'ε'})
                    if 'ε' not in first[symbol]:
                        break
                else:
                    new_production.append(symbol)
            else:
                new_production += list(follow[key])
            ll1_productions[key].append(' '.join(new_production))
    return ll1_productions
# 打印结果
first = first_set(productions)
follow = follow_set(productions, first)
ll1_productions = ll1_grammar(productions, first, follow)
# print('LL(1)文法:')
# for key in ll1_productions:
#     print(key, '→', ' | '.join(ll1_productions[key]))
# print('First集合:')
# for key in first:
#     print(key, ':', first[key])
# print('Follow集合:')
# for key in follow:
#     print(key, ':', follow[key])
'''

'''
# 定义文法的产生式
productions = {
    'E': ['T E\''],
    'E\'': ['+ T E\'', 'ε'],
    'T': ['int', 'float', 'double', 'long'],
    'B': ['U B\''],
    'B\'': ['and U B\'', 'ε'],
    'U': ['true', 'false'],
    'V': ['var'],
    'A': ['V = E', 'B'],
    'C': ['if ( B ) L else L'],
    'S': ['A', 'C'],
    'L': ['S ; L', 'S'],
    'P': ['L']
}
# 计算文法的First集
def first_set(productions, symbol, first):
    # 如果已经计算过该符号的First集，则直接返回
    if symbol in first:
        return
    # 初始化该符号的First集为空集
    first[symbol] = set()
    # 遍历该符号的每个产生式
    for production in productions[symbol]:
        # 如果该产生式的第一个符号是终结符号，则将该终结符号加入First集
        if production[0] not in productions.keys():
            first[symbol].add(production[0])
        else:
            # 否则，遍历该产生式的每个符号
            for i in range(len(production)):
                # 递归计算该符号的First集
                first_set(productions, production[i], first)
                # 将该符号的First集加入该符号所在产生式的First集
                first[symbol] |= (first[production[i]] - {'ε'})
                # 如果该符号的First集不包含空串，则跳出循环
                if 'ε' not in first[production[i]]:
                    break
    else:
        # 如果该产生式的所有符号的First集都包含空串，则将空串加入该符号的First集
        first[symbol].add('ε')
# 计算文法的Follow集
def follow_set(productions, first):
    # 初始化每个非终结符的Follow集为空集
    follow = {}
    for key in productions:
        follow[key] = set()
    # 将起始符号的Follow集加上结束符号'$'
    follow['P'].add('$')
    # 重复进行以下步骤，直到不再有新的符号加入Follow集
    while True:
        updated = False
        # 遍历每个非终结符号的每个产生式
        for key in productions:
            for production in productions[key]:
                # 遍历产生式中的每个符号
                for i, symbol in enumerate(production):
                    # 如果当前符号是一个非终结符号
                    if symbol in productions.keys():
                        # 如果当前符号是产生式的最后一个符号
                        if i == len(production) - 1:
                            # 将该非终结符的Follow集加上该非终结符所在产生式所在非终结符的Follow集
                            follow[symbol] |= follow[key]
                        else:
                            # 遍历当前符号后面的所有符号
                            for j in range(i+1, len(production)):
                                # 如果该符号的First集非空
                                if production[j] in first.keys():
                                    # 将该非终结符号的Follow集加上该符号的First集
                                    follow[symbol] |= first[production[j]]
                                    # 如果该符号的First集不包含空串，则跳出循环
                                    if 'ε' not in first[production[j]]:
                                        break
                                else:
                                    # 如果该符号是终结符号，则将其加入该非终结符的Follow集
                                    follow[symbol].add(production[j])
                                    break
                            else:
                                # 如果符号后面的所有符号的First集都包含空串，则将该非终结符的Follow集加上该非终结符所在产生式所在非终结符的Follow集
                                follow[symbol] |= follow[key]
        # 如果没有新的符号加入Follow集，则跳出循环
        if not updated:
            break
    # 返回所有非终结符的Follow集
    return follow
# 计算文法的First集
first = {}
for key in productions.keys():
    first_set(productions, key, first)
# 计算文法的Follow集
follow = follow_set(productions, first)
# 输出LL(1)文法
print('LL(1)文法:')
for key in productions.keys():
    print(key, '→', ' | '.join(productions[key]))
# 输出First集合
print('First集合:')
for key in first.keys():
    print(key, ':', first[key])
# 输出Follow集合
print('Follow集合:')
for key in follow.keys():
    print(key, ':', follow[key])
'''

with open('output.txt', 'r', encoding='utf-8') as f:
    for line in f:
        print(line, end='')