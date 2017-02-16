import sys

input_filename = sys.argv[1]

with open(input_filename) as f:
    content = f.readlines()
content = [x.strip() for x in content]

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
