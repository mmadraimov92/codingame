import sys
import math

l_x, l_y, i_tx, i_ty = [int(i) for i in input().split()]

# game loop
while True:
    remaining_turns = int(input())
    ans = ''
    if l_y > i_ty:
        ans += 'S'
        i_ty += 1
    if l_y < i_ty:
        ans += 'N'
        i_ty -= 1
    if l_x > i_tx:
        ans += 'E'
        i_tx += 1
    if l_x < i_tx:
        ans += 'W'
        i_tx -= 1
    print(ans)