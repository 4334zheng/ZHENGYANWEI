
import time
myList = list(range(1,10))
list1 = [10]
start = time.time()
t = 100000
while t != 0:
    myList = myList + list1
    t -= 1
print(time.time()-start)

import time
myList = list(range(1,10))
start = time.time()
t = 10000000
while t != 0:
    myList.append(10)
    t -= 1
print(time.time()-start)