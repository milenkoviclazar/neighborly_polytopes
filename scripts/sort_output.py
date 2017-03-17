import sys
import re
from utils import get_content

content = get_content(sys.argv[1])

data = {}
curr_polytope = None
for line in content:
    if "polytope" in line:
        curr_polytope = line
        data[curr_polytope] = []
    if line is not None:
        data[curr_polytope].append(line)

output_filename = sys.argv[2]
f = open(output_filename, 'w')
for k, v in sorted(data.items(), key=lambda x: int(re.findall('\d+', x[0])[0])):
    for entry in v:
        f.write(entry + "\r\n")
