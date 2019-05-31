n = int(input())
number_list = []
for i in input().split():
    number_list.append(int(i))

cost_list = []
while len(number_list) > 1:
    a = min(number_list)
    number_list.pop(number_list.index(a))
    b = min(number_list)
    number_list.pop(number_list.index(b))
    cost_list.append(a+b)
    number_list.append(a+b)

print(sum(cost_list))
