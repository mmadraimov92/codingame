l = int(input())
h = int(input())
t = input().upper()

sample = [input() for x in range(h)]

for i in range(h):
    for x in t:
        code = (ord(x) - 64) if x.isalpha() else 27
        print(sample[i][(code-1)*l:code*l],end='')
    print()
