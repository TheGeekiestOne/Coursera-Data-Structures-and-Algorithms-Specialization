#Uses python3

import sys

def optimal_summands(n):
    summands = []
    i from 1 to n + 1
        if last_number(i, n):
            #found the last one, append to summands and break.
            summands.append(i)
        
        #otherwise, append i to summands, n = n - i and increase i by 1.
        summands.append(i)
        n = n - i
        i = i +1

    return summands

def last_number(i, n):
    check that i * 2 >= n. If true, you got the last one

def largest_number(a):
    res = ""
    i = 0
    while len(a) > 0:
        i = i+ 1
        sMax = find_safe_max_number(a)
        res += sMax
        a.remove(sMax)

    return res

def find_safe_max_number(a):
    max_ = a[0]
    for x in a:
        max_ = safe_max(max_, x)
    return max_

def safe_max(max_, x):
    # A = str(max_) + str(x)
    # B = str(x) + str(max_)
    # Check A > B ? max_ : x

if __name__ == '__main__':
    input = sys.stdin.read()
    data = input.split()
    a = data[1:]
    print(largest_number(a))
    
