#!/usr/bin/env python
import os
import sys

#reemplazar con el ejemplo 1-2-3
os.system( 'g++ src/*.cpp Example2.cpp -o a.out')
os.system( './a.out')

import numpy as np
import matplotlib.pyplot as plt
T = np.loadtxt("dat/Triangles.dat");

xa = np.array([])
ya = np.array([])
for t in T:
    Nodes = np.array_split(t,3)
    for node in Nodes:
        xa = np.append(xa, node[0])
        ya = np.append(ya, node[1])
        
Gamma = np.sin(np.pi*xa)*np.sin(np.pi*ya)/(-2*np.pi**2)

from mpl_toolkits.mplot3d import Axes3D
DataAll1D = np.column_stack((xa, ya, Gamma))
# create 2d x,y grid (both X and Y will be 2d)
X, Y = np.meshgrid(DataAll1D[:,0], DataAll1D[:,1])

# repeat Z to make it a 2d grid
Z = np.tile(DataAll1D[:,2], (len(DataAll1D[:,2]), 1))

fig = plt.figure(figsize=(7, 5))
ax = fig.add_subplot(111, projection='3d')

ax.plot_surface(X, Y, abs(Z), cmap="rainbow")
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('U(x, y)')
plt.savefig("dat/fx2.png")

