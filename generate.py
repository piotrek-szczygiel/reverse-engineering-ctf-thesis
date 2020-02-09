import random

flag = "SCTF{v1Rtu4L_MaCH1n3s_aR3_FuN}"
max = 0x7FFF

for f in flag[::-1]:
    x = ord(f)
    rand = random.randint(0, max // x)
    neg = ~(rand * x)
    print("push", ~(rand * x))
    print("push", rand)
