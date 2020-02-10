import random

flag = input()
max = 0x7FFF

for f in flag[::-1]:
    x = ord(f)
    rand = random.randint(0, max // x)
    print("push", ~(rand * x))
    print("push", rand)
