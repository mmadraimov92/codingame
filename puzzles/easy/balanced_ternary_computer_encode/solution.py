def int_to_bt(n):
    result = ''
    negative = False
    if n == 0:
        return '0'
    if n < 0:
        negative = True
    n = abs(n)

    while n > 0:
        m = n%3
        if m == 2:
            result += 'T'
            n += 1
        elif m == 1:
            result += '1'
            n -= 1
        elif m == 0:
            result += '0'
        n = n / 3

    if negative:
        str1 = '1T'
        str2 = 'T1'
        mapped = str.maketrans(str1, str2)

        return result[::-1].translate(mapped)
    else:
        return result[::-1]

n = int(input())
print(int_to_bt(n))
