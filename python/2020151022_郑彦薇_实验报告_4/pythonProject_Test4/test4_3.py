#(1)
List = ['apple', 'orange', 'pear']
res = [str.upper()[0] for str in List]
print(res)

#(2)
List = ['apple', 'orange', 'pear']
res = [str for str in List if len(str) < 6]
print(res)

#(3)
List = ["TA_path", "student_poohbear", "TA_michael", "TA_guido", "student_htiek"]
res = [str.split('_')[1] for str in List if str.split('_')[0] == "TA"]
print(res)

#(4)
List = ['apple', 'orange', 'pear']
res = [(str, len(str)) for str in List]
print(res)

#(5)
List = ['apple', 'orange', 'pear']
res = {str: len(str) for str in List}
print(res)

