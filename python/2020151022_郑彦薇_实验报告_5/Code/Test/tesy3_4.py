#1
'''
d = {[1,2]:1,[3,4]:3}
print(d)
d = {(1,2):1,(3,4):3}
print(d)
d = {{1,2}:1,{3,4}:3}
print(d)
d = {"12":1,"34":3}
print(d)
'''
#2
D = {"what":22, "are":11, "you":14, "doing":5, "next":9, "Saturday?":4}
sum = 0
for x in D.items():
    sum = sum+D[x[0]]#a
    #sum = sum + x[1] #b
print(sum)