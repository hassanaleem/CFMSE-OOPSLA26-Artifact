# Usage: python create_summary_excel.py <MODE> <DIR> class1 class2 class3 ..
# <MODE>: ALL STATE STRUCTURE
# <DIR>: directory where to dump the generated file and where the similarity traces are stored
#

import csv
import collections
import sys
import os.path

reader = csv.reader(open(sys.argv[1], "rb"), delimiter=';')
rows = list(reader)
total=0
b_dic = collections.OrderedDict()
for row in rows:
        parts=row[3][1:len(row[3])-2].split(' x ')
        size=(parts[1][1:] if parts[1][0] == "i" else -1)
        if size < 0:
                continue
        if size[len(size)-1] == "*":
                size=64
        bytes=(int(parts[0])*int(size))/8
        total+=bytes
        if b_dic.has_key(bytes) :
                b_dic[bytes] = b_dic.get(bytes)+1
        else:
                b_dic[bytes] = 1

for a in range(1, max(b_dic.keys())+1):
        if b_dic.has_key(a):
                print(str(a)+';'+str(b_dic[a]))

print("Total bytes: " + str(total))