import sys
from utils import get_content

content = get_content(sys.argv[1])
count = 0
prevline = ""
for idx, line in enumerate(content):
    if len(line) == 0 and len(prevline) != 0:
        count += 1

    prevline = line
print(count)