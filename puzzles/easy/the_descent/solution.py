import sys
import math

while True:
    m = 0
    for i in range(8):
        h = int(input())
        if h >= m:
            m = h
            h_index = i

    # To debug: print("Debug messages...", file=sys.stderr)

    print(h_index)