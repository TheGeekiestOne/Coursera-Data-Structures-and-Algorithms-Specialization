# Uses python3
import sys
from collections import namedtuple

Segment = namedtuple('Segment', 'start end')

def optimal_points(segments):
    points = []

    while(len(segments) > 0):
        min_right = choose_min_right_segment(segments) 
        points.append(min_right)
        loop i < len(segments):
            if include_point(segments[i], min_right):
                del segments[i]
            else:
                i = i + 1

    return points

def include_point(segment, point):
    #to check segment has segment.start <= point <= segment.end

def choose_min_right_segment(segments):
    #choose the minmum right value in segments. Just loop through segments and choose min_right

if __name__ == '__main__':
    input = sys.stdin.read()
    n, *data = map(int, input.split())
    segments = list(map(lambda x: Segment(x[0], x[1]), zip(data[::2], data[1::2])))
    points = optimal_points(segments)
    print(len(points))
    for p in points:
        print(p, end=' ')
