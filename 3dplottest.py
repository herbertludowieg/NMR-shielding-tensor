#!/usr/bin/python

from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import sys

def mult(x,y,z):
  return x**2*tensor[0][0]+y**2*tensor[1][1]+z**2*tensor[2][2]+ \
         x*y*2*tensor[0][1]+x*z*2*tensor[0][2]+y*z*2*tensor[1][2]

def main():
  phi = np.linspace(0,np.pi,500)
  theta = np.linspace(0,2*np.pi,500)
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

  g = np.zeros((len(X),len(X[0])))
  for i in range(len(X)):
    for j in range(len(X[0])):
      g[i][j] = mult(X[i][j],Y[i][j],Z[i][j])
  THETA,PHI = np.meshgrid(theta,phi)
  #print THETA,PHI
  #x = g * np.sin(PHI) * np.cos(THETA)
  #y = g * np.sin(PHI) * np.sin(THETA)
  #z = g * np.cos(PHI)
  x = g * X
  y = g * Y
  z = g * Z
  print len(x),len(x[0])
  fig = plt.figure()
  ax = fig.add_subplot(111,projection='3d')
  cset = ax.plot_surface(x,y,z)
  plt.show()

tensor = []
if len(sys.argv) < 2:
  print "Could not parse arguments"
  print "USAGE: "+sys.argv[0]+" [tensor file]"
  sys.exit()
fn = open(sys.argv[1],'r')
for i in fn.readlines():
  tensor.append([])
  d = i.split()
  for j in d:
    tensor[len(tensor)-1].append(float(j))
main()
