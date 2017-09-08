#!/usr/bin/python

from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
#import matplotlib
#matplotlib.use("TkAgg")

def mult(x,y,z):
  tensor = [[100.472,91.193,-4.279], \
            [91.193,67.572,-1.544], \
            [-4.279,-1.544,-2.329]]
  return x**2*tensor[0][0]+y**2*tensor[1][1]+z**2*tensor[2][2]+ \
         x*y*2*tensor[0][1]+x*z*2*tensor[0][2]+y*z*2*tensor[1][2]

def main():
  phi = np.linspace(0,np.pi,200)
  theta = np.linspace(0,2*np.pi,200)
  X = []
  Y = []
  Z = []
  for i in phi:
    X.append([])
    Y.append([])
    Z.append([])
    for j in theta:
      X[len(X)-1].append(np.sin(i)*np.cos(j))
      Y[len(Y)-1].append(np.sin(i)*np.sin(j))
      Z[len(Z)-1].append(np.cos(i))
      #print X
  g = np.zeros((len(X),len(X[0])))
  for i in range(len(X)):
    for j in range(len(X[0])):
      g[i][j] = mult(X[i][j],Y[i][j],Z[i][j])
  THETA,PHI = np.meshgrid(theta,phi)
  x = g * np.sin(PHI) * np.cos(THETA)
  y = g * np.sin(PHI) * np.sin(THETA)
  z = g * np.cos(PHI)
  fig = plt.figure()
  ax = fig.add_subplot(111,projection='3d')
  cset = ax.plot_surface(x,y,z)
  plt.show()

main()
