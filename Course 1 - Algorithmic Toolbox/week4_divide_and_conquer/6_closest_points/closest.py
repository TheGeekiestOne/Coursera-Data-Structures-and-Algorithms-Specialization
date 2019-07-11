

#Uses python3
import sys
import math
import random

# There is a chapter in [CLRS] discuss about this problem, I think this problem
# is hardest in this course. I usually encounter with Failed case
# #22/23: time limit exceeded. So, be sure that you read [CLRS] textbook,
# [section 33.4] about this problem first.
#
# We need to pre-sort points by x coordinate and divide points into 2 arrays:
# left_points and right_points. Our goal is calculate min distance of left_points
#  called min_left, min distance of right_points called min_right. And min
#   distance between left_points and right_points called hybrid_min.


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return str([self.x, self.y])

def distance(p1, p2):
    return ((p1.x - p2.x) ** 2 + (p1.y - p2.y) ** 2) **0.5

def construct_points(x, y):
    points = []
    for i in range(len(x)):
        points.append(Point(x[i], y[i]))
    return points

def minimum_distance(x, y):
    points = construct_points(x, y)
    sorted_p_x = sorted(points, key=lambda p: p.x)

    return large_size_min_distance(sorted_p_x)

def small_size_min_distance(points):
    result = sys.maxsize
    for i in range(len(points)):
        for j in range(i+1, len(points)):
            result = min(result, distance(points[i], points[j]))
    return result

def large_size_min_distance(p_x):
    size = len(p_x)
    half_size = int(len(p_x)/2)

    if size <= 3:
        return small_size_min_distance(p_x)

    left_p_x = p_x[0:half_size]
    right_p_x = p_x[half_size:size]

    left_min = large_size_min_distance(left_p_x)
    right_min = large_size_min_distance(right_p_x)
    separated_min = min(left_min, right_min)

    line_l = (left_p_x[-1].x + right_p_x[0].x)/2
    hybrid_min = compute_hybrid_min(left_p_x, right_p_x, line_l, separated_min)

    return min(separated_min, hybrid_min)

def compute_hybrid_min(left_x, right_x, line_l, wide):
    left = []
    for i in range(len(left_x)):
        if abs(left_x[i].x - line_l) <= wide:
            left.append(left_x[i])
    right = []
    for i in range(len(right_x)):
        if abs(right_x[i].x - line_l) <= wide:
            right.append(right_x[i])
    total = left + right

    total = sorted(total, key=lambda p: p.y)

    result = wide
    for i in range(len(total)):
        for j in range(i + 1, min(i+8, len(total))):
            if abs(total[i].y - total[j].y) <= wide:
                result = min(result, distance(total[i], total[j]))

    return result

if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n = data[0]
    x = data[1::2]
    y = data[2::2]
    print("{0:.9f}".format(minimum_distance(x, y)))
