import sys
import math

n = int(input())
horse_list = []
for i in range(n):
    horse_list.append(int(input()))

horse_list.sort()
m = sys.maxsize
for i in range(n-1):
    if abs(horse_list[i] - horse_list[i+1]) < m:
        m = abs(horse_list[i] - horse_list[i+1])

print(m)
