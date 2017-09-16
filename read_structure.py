#!/usr/bin/python

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

def open_file(file):
  fn = open(file)
  x = []
  for i in fn.readlines():
    if i[0] == '#':
      continue
    x.append([])
    d = i.split()
    for j in d:
      x[-1].append(float(j))
  return x

def open_file_bonds(file):
  fn = open(file)
  x = []
  for i in fn.readlines():
    if i[0] == '#':
      continue
    d = i.split()
    x.append([])
    for j in d:
      if int(j) == -1:
        continue
      x[-1].append(int(j))
  return x

def transpose(x):
  y = np.zeros((len(x[0]),len(x)))
  for i in range(len(x[0])):
    for j in range(len(x)):
      y[i][j] = x[j][i]
  return y

def main():
  coord = open_file("coordinates.structure.dat")
  coordt = transpose(coord)
  bonds = open_file_bonds("sorted.structure.dat")
  tens_x = open_file("x.tensor.dat")
  tens_y = open_file("y.tensor.dat")
  tens_z = open_file("z.tensor.dat")
  fig = plt.figure()
  ax = Axes3D(fig)
  ax.scatter(coordt[0],coordt[2],coordt[1],c='b')
  ax.plot_surface(tens_x,tens_z,tens_y)
  for i in range(len(bonds)):
    for j in range(1,len(bonds[i])):
      x = [coord[bonds[i][0]][0],coord[bonds[i][j]][0]]
      y = [coord[bonds[i][0]][1],coord[bonds[i][j]][1]]
      z = [coord[bonds[i][0]][2],coord[bonds[i][j]][2]]
      ax.plot(x,z,y,'-b')
  plt.show()

main()
