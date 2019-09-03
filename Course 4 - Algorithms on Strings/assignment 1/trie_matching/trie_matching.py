# python3
import sys

NA = -1

class Node:
	def __init__ (self):
		self.next = [NA] * 4

def solve (text, n, patterns):
	result = []

	// write your code here

	return result

text = sys.stdin.readline ().strip ()
n = int (sys.stdin.readline ().strip ())
patterns = []
for i in range (n):
	patterns += [sys.stdin.readline ().strip ()]

ans = solve (text, n, patterns)

sys.stdout.write (' '.join (map (str, ans)) + '\n')
