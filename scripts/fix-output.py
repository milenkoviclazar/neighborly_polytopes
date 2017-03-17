import sys
from utils import get_content

content = get_content(sys.argv[1])

output_filename = sys.argv[2]
f = open(output_filename, 'w')
for line in content:
    if "polytope" in line:
        prevline = line
    elif "elapsed" in line:
        pass
    else:
        if prevline is not None:
            f.write(prevline + "\r\n")
            prevline = None
        f.write(line + "\r\n")
f.close()
