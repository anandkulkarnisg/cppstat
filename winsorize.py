#!/usr/bin/python3

import scipy.stats
import numpy as np
import sys

def printArrayToConsole(phase, arr):
    size=len(arr)
    print(phase,'',end='')
    for i in range(size-1):
        print(arr[i], ', ', end='')
    print(arr[size-1])

winSize=float(sys.argv[1])
a=np.array([92,19,101,58,1053,91,26,78,10,13,-40,101,86,85,15,89,89,28,-5,41])
#a=np.array([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20])
printArrayToConsole('before : ', a)
a=scipy.stats.mstats.winsorize(a, limits=(float(winSize), float(winSize)), inclusive=(True, True))
printArrayToConsole('after : ', a)
