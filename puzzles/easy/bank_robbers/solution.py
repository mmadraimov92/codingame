import sys

robber_count = int(input()) # robers number
vault_count = int(input()) # number of vaults: if v 10 then 0,1, .. 9
vault_times = [] # list of vault total time to try all combinations
uniques_digits = 10
unique_vowels = 5
robber_time = [{"id": i, "time": 0} for i in range(robber_count)]

for i in range(vault_count):
    c, n = [int(j) for j in input().split()]
    time = (uniques_digits ** n) * (unique_vowels ** (c - n))
    vault_times.append(time)


for t in vault_times:
    robber = min(robber_time, key=lambda r: (r["time"], r["id"]))
    robber["time"] += t

print(max(robber_time, key=lambda r: r["time"])["time"])


