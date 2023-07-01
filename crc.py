import re

data = input("Enter a binary string : ")
poly = input("Enter FCS polynomial : ")
pos = re.findall(r'\d+', poly)
print(pos)
for i in reversed(pos):
    print(i)