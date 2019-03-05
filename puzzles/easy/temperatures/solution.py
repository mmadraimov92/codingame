import sys
import math

n = int(input())  # the number of temperatures to analyse
temps = [int(x) for x in input().split()]  # the n temperatures expressed as integers ranging from -273 to 5526
d = sys.maxsize
closest = 0
for i in range(n):
    if d == abs(temps[i]) and temps[i] > 0:
        closest = temps[i]
    if d > abs(temps[i]):
        d = abs(temps[i])
        closest = temps[i]
print(closest)