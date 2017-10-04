#!/usr/bin/python

import sys
# In order to make python3 work
if sys.version[0] == '3':
  import matplotlib
  matplotlib.use("TkAgg")

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
  # opens the files created with the C++ script
  coord = open_file("coordinates.structure.dat")
  # to make python happy
  coordt = transpose(coord)

  bonds = open_file_bonds("sorted.structure.dat")
  tens_x = open_file("x.tensor.dat")
  tens_y = open_file("y.tensor.dat")
  tens_z = open_file("z.tensor.dat")
  # finds out how many tensors were calculated based on the size of the data
  number_figs = len(tens_x) / len(tens_x[0])


  fig = plt.figure()
  ax = Axes3D(fig)
  #ax = fig.add_subplot(111,projection='3d')
  ax.set_aspect(1)
  ax.scatter(coordt[0],coordt[2],coordt[1],c='b')
  # will make a line that signifies a bond in the structure
  # bonds is a file that comes from sorting and finding the closest atoms
  # with the C++ script
  for i in range(len(bonds)):
    for j in range(1,len(bonds[i])):
      #print i,bonds[i]
      x = [coord[bonds[i][0]][0],coord[bonds[i][j]][0]]
      y = [coord[bonds[i][0]][1],coord[bonds[i][j]][1]]
      z = [coord[bonds[i][0]][2],coord[bonds[i][j]][2]]
      ax.plot(x,z,y,'-b')
  i = 0
  while ( i < number_figs ):
    ax.plot_surface(tens_x[i*len(tens_x[0]):(i+1)*len(tens_x[0])-1], \
                    tens_z[i*len(tens_z[0]):(i+1)*len(tens_z[0])-1], \
                    tens_y[i*len(tens_y[0]):(i+1)*len(tens_y[0])-1])
    i+=1

  ax.set_xlim(-15,15)
  ax.set_ylim(-15,15)
  ax.set_zlim(-15,15)
  
  plt.show()

main()
