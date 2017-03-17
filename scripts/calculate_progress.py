import sys
from utils import get_content

content = get_content(sys.argv[1])

mini = 9999999
prev = -1
for line in content:
    if "polytope" in line:
        prevline = line
        _, b = line.split()
        b = b[:-1]
        num = int(b)
        if num < prev:
            mini = min(mini, prev)
        prev = num

mini = min(mini, prev)

print(mini)
