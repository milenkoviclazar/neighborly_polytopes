import sys
from utils import get_content

content = get_content(sys.argv[1])
indices = []
for line in content:
    if "polytope" in line:
        indices.append(line.split()[1][:-1])


content = get_content(sys.argv[2])
f = open(sys.argv[3], 'w')
for line in content:
    for idx in indices:
        if line.startswith(str(idx) + ':'):
            f.write(line + '\r\n')
