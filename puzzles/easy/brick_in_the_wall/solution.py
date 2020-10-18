x = int(input())
n = int(input())
bricks = sorted([int(i) for i in input().split()], reverse=True)
total_work = 0
level = 1
bricks_in_row = 0
for b in bricks:
    total_work += 10 * b * ((level-1)*0.065)
    bricks_in_row += 1
    if bricks_in_row == x:
        level += 1
        bricks_in_row = 0

print("{:.3f}".format(total_work))
