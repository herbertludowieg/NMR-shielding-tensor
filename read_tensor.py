#!/usr/bin/python

from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib
import numpy as np

def open_file(file):
  fn = open(file)
  x = []
  for i in fn.readlines():
    if i[0] == '#':
      continue
    d = i.split()
    x.append([])
    for j in d:
      x[-1].append(float(j))
  return x

def main():
  X = open_file("x.tensor.dat")
  Y = open_file("y.tensor.dat")
  Z = open_file("z.tensor.dat")
  totFigs = len(X) / len(X[0])
  for i in range(totFigs):
    fig = plt.figure(i+1)
  
    ax = Axes3D(fig)
    cset = ax.plot_surface(X[i*len(X[0]):(i+1)*len(X[0])], \
                           Y[i*len(Y[0]):(i+1)*len(Y[0])], \
                           Z[i*len(Z[0]):(i+1)*len(Z[0])])
  
#  ax = fig.add_subplot(111,projection='3d')
#  cset = ax.plot_surface(X,Y,Z)
  plt.show()

main()
