import sys
from utils import get_content

infilename = sys.argv[1]
outfilename = infilename[:-3] + "solved"
content = get_content(infilename)

solved = []


for line in content:
    if "polytope" in line:
        numb = line.split(" ")[1]
        numb = numb[:-1]
        numb = int(numb)
        solved.append(numb)

f = open(outfilename, 'w')
f.write(str(len(solved)))
f.write("\n")
for x in solved:
    f.write(str(x) + " ")
f.write("\n")
f.close()
