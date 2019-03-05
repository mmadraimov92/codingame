import sys
import math

message = input()
bmessage = ''.join(format(ord(x), '07b') for x in message)
one = False
zero = False
answer = ''
for x in bmessage:
    if x == '1':
        zero = False
        if not one:
            answer += ' 0 0'
            one = True
        else:
            answer += '0'
    if x == '0':
        one = False
        if not zero:
            answer += ' 00 0'
            zero = True
        else:
            answer += '0'

print(answer[1:])