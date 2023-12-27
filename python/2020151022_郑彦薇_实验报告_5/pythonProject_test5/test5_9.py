import itertools
def sum0(lst):
    for length in range(1, 9):
        subset = itertools.combinations(lst, length)
        for i in subset:
            if sum(i) == 0:
                return True
    return False

lst = [2, 3, 4, 5, 6, 7, 8, 9]
if sum0(lst):
    print("True")
else:
    print("False")
