#!/usr/bin/env python
import os
import sys

os.system( 'g++ src/Point.cpp src/Triangle.cpp src/Triangulation.cpp Example1.cpp -o a.out')
os.system( './a.out')

import numpy as np
import matplotlib.pyplot as plt

files = ["nodesS1", "nodesS2"];
for i, f in enumerate(files):
    x, y = np.loadtxt("dat/"+f+".dat", unpack=True)
    plt.plot(x, y, '.')
    
files = ["S1","S2","NotS1S2"]#, "S2", "NotS1S2"];
colors = ['k', '#61458a', 'r']

for i, f in enumerate(files):
    f = "dat/"+f+"Triangles.dat";
    if(os.path.getsize(f)>0): 
        x = np.loadtxt(f)
        shape = np.asarray(x.shape)
        if(len(shape)==1):
            coord = [[x[0], x[1]], [x[2], x[3]], [x[4], x[5]]]
            coord.append(coord[0]) #repeat the first point to create a 'closed loop'
            xs, ys = zip(*coord) #create lists of x and y values
            plt.plot(xs,ys, colors[i], linewidth=0.5)
        else:
            for xx in x:
                coord = [[xx[0], xx[1]], [xx[2], xx[3]], [xx[4], xx[5]]]
                coord.append(coord[0]) #repeat the first point to create a 'closed loop'
                xs, ys = zip(*coord) #create lists of x and y values
                plt.plot(xs,ys, colors[i], linewidth=0.5)
    else:
        print(f)
plt.savefig("mesh.eps")
plt.show()
''''''
