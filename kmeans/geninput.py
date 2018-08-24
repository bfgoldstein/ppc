import sys
from random import uniform as uni
# k = 50 & n = 1000000 for the contest
k = int(sys.argv[1])
n = int(sys.argv[2])

print k
print n
for i in range(k+n):
	print "%f %f %f" %(uni(-100,100), uni(-100,100), uni(-100,100))

