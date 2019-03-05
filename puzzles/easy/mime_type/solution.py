import sys
import math

n = int(input())  # Number of elements which make up the association table.
q = int(input())  # Number Q of file names to be analyzed.
mimetype = {}
for i in range(n):
    ext, mt = input().split()
    mimetype[ext.lower()] = mt
for i in range(q):
    try:
        fname, fext = input().rsplit('.',1)  # One file name per line.
        print (mimetype.get(fext.lower(),'UNKNOWN'))
    except:
        print('UNKNOWN')