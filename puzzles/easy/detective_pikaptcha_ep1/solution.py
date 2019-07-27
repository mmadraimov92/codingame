import sys
import math


width, height = [int(i) for i in input().split()]

game_map = []
for i in range(height):
    line = input()
    game_map.append(list(line))

def get_adjacent_count(h,w):
    count = 0
    try:
        if w != width and game_map[h][w+1] != '#':
            count += 1
    except:
        pass
    try:
        if  w != 0 and game_map[h][w-1] != '#':
            count += 1
    except:
        pass
    try:
        if  h != height and game_map[h+1][w] != '#':
            count += 1
    except:
        pass
    try:
        if h != 0 and game_map[h-1][w] != '#':
            count += 1
    except:
        pass
    return count

for i in range(height):
    for j in range(width):
        if game_map[i][j] == "#":
            print("#", end='')
        else:
            print(get_adjacent_count(i,j), end='')
    print("")
