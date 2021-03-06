#!/usr/bin/env python
import os
import sys

#reemplazar con el ejemplo 1-2-3
os.system( 'g++ src/*.cpp Example2.cpp -o a.out')
os.system( './a.out')

import numpy as np
import matplotlib.pyplot as plt

xN, yN = np.loadtxt("dat/Nodes.dat", unpack=True)
plt.plot(xN, yN, 'co')

T = np.loadtxt("dat/Triangles.dat");
for x in T:
    coord = [[x[0], x[1]], [x[2], x[3]], [x[4], x[5]]]
    coord.append(coord[0]) #repeat the first point to create a 'closed loop'
    xs, ys = zip(*coord) #create lists of x and y values
    plt.plot(xs,ys, 'k', linewidth=0.5)

plt.xlabel("x [u.a]")
plt.ylabel("y [u.a]")
plt.savefig("dat/mesh.png")

xa = np.array([])
ya = np.array([])

for t in T:
    Nodes = np.array_split(t,3)
    for node in Nodes:
        xa = np.append(xa, node[0])
        ya = np.append(ya, node[1])
A, B, C, Gamma = np.loadtxt("dat/Results.dat", unpack=True)
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
plt.savefig("dat/fx.png")

