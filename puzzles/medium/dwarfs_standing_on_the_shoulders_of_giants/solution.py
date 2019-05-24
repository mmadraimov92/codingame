import sys
import math

graph = {}

n = int(input())
for i in range(n):
    x, y = [int(j) for j in input().split()]
    graph.setdefault(x,[]).append(y)

print(graph, file=sys.stderr)

def find_length(start):
    longest = 1
    if start not in graph:
        return longest
    for p in graph[start]:
        l = find_length(p) + 1
        if l >= longest:
            longest = l
    return longest

longest = 1
for node in graph:
    l = find_length(node)
    if longest <= l:
        longest = l

print(longest)
