productions = {}
def build_tree(symbol):
    if symbol.isupper and symbol in productions.keys():
        children = []
        