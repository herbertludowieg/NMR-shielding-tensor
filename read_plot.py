#!/usr/bin/python

from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

def main():
  fn = open("xyz.tensor.dat",'r')
  x = []
  y = []
  z = []
  for i in fn.readlines():
    if i[0] == '#':
      continue
    d = i.split()
    x.append(float(d[0]))
    y.append(float(d[1]))
    z.append(float(d[2]))
  X = np.zeros((int(np.sqrt(len(x))),int(np.sqrt(len(x)))))
  Y = np.zeros((int(np.sqrt(len(x))),int(np.sqrt(len(x)))))
  Z = np.zeros((int(np.sqrt(len(x))),int(np.sqrt(len(x)))))
  print len(X),len(X[0])
  #Y = np.zeros((np.sqrt(len(x)),np.sqrt(len(x))))
  #Z = np.zeros((np.sqrt(len(x)),np.sqrt(len(x))))
  for i in range(len(X)):
    for j in range(len(X[0])):
      X[i][j] = x[i*len(X)+j]
      Y[i][j] = y[i*len(X)+j]
      Z[i][j] = z[i*len(X)+j]
  print len(X),len(X[0])
  fig = plt.figure()
  ax = fig.add_subplot(111,projection='3d')
  cset = ax.plot_surface(x,y,z)
  plt.show()
  print X

main()
