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

def transpose(x):
  y = np.zeros((len(x[0]),len(x)))
  for i in range(len(x[0])):
    for j in range(len(x)):
      y[i][j] = x[j][i]
  return y

def main():
  coord = open_file("coordinates.structure.dat")
  coord = transpose(coord)
  tens_x = open_file("x.tensor.dat")
  tens_y = open_file("y.tensor.dat")
  tens_z = open_file("z.tensor.dat")
  fig = plt.figure()
  ax = Axes3D(fig)
  ax.scatter(coord[0],coord[2],coord[1])
  ax.plot_surface(tens_x,tens_z,tens_y)
  plt.show()

main()
