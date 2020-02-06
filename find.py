magic = []
for f in [126, 86, 49, 114, 84, 117, 97, 108, 95, 109, 52, 99, 104, 49, 110, 51]:
    for x in range(256):
        result = f + x
        if result > 255:
            continue
        result ^= x
        if result == 77:
            magic.append(x)
            continue
print(magic)
