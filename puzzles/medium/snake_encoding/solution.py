s = []
n = int(input())
x = int(input())
for i in range(n):
    s.append(list(input()))

for i in range(x):
    tmp = s[n-1][n-1] if (n % 2) == 0 else s[0][n-1] # head of a snake
    for j in range(n):
        if ((j+1) % 2 == 1): # odd columns
            for k in reversed(range(n)):
                tmp2 = s[k][j]
                s[k][j] = tmp
                tmp = tmp2
        else:
            for k in range(n): # even columns
                tmp2 = s[k][j]
                s[k][j] = tmp
                tmp = tmp2
for line in s:
    print("".join(line))
