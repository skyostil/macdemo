import math

size = 256
shift = 16

print "const int sintab[%d] =" % size
print "{"
print "   ",

for i in range(size):
    print "%d," % int(float(1 << shift) * math.sin(2 * math.pi * i / float(size))),
    if not i % 8:
        print
        print "   ",

print
print "};"
