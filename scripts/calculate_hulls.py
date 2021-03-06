from scipy.spatial import ConvexHull
import sys
from utils import get_content

def fraction_to_float(s):
    if s.find("/") == -1:
        return float(s)
    a, b = s.split("/")
    return float(a) / float(b)


def parse_array(s):
    ret = []
    for part in s.split(","):
        part = part.strip()
        ret.append(fraction_to_float(part))
    return ret


def opposite_bracket(c):
    if c == "]":
        return "["
    return "("


def parse(s):
    ret = []
    stack = []
    for c in s:
        if c == "]" or c == ")":
            tmp = ""
            x = stack.pop()
            while x != opposite_bracket(c):
                tmp += x
                x = stack.pop()
            tmp = tmp[::-1]
            ret.append(parse_array(tmp))
        else:
            stack.append(c)
    return ret

content = get_content(sys.argv[1])

output_filename = input_filename.replace(".txt", ".hull")
print(output_filename)
f = open(output_filename, 'w')


for idx, line in enumerate(content):
    print(idx)
    line = line[line.find("[") + 1:-1]
    points = parse(line)
    hull = ConvexHull(points, qhull_options="").simplices.tolist()
    n = len(points)
    perm = [-1] * n
    cnt = 0
    for simplex in hull:
        for i, x in enumerate(simplex):
            if perm[simplex[i]] == -1:
                perm[simplex[i]] = cnt
                cnt += 1
            simplex[i] = perm[simplex[i]]

    f.write(str(idx) + ": " + str(hull).replace(" ", "") + '\r\n')
