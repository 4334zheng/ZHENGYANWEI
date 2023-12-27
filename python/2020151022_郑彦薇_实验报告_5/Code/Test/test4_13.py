from time import time
def timed(fn):
    def time_fn():
        start = time()
        fn()
        end = time()
        count = (end - start)*1000
        print(f'time is {count} ms')
    return time_fn
@timed
def test_plus():
    result = []
    for i in range(100000):
        result = result + [i]
@timed
def test_append():
    result = []
    for i in range(100000):
        result.append(i)

test_plus()
test_append()
