#!/bin/usr/python

import numpy

def main():
  file = "../nanoccapped.xyz"
  fn = open(file,'r')
  x = []
  y = []
  z = []
  for i in fn.readlines():
    d = i.split()
    if len(d) < 4:
      continue
    x.append(float(d[-3]))
    y.append(float(d[-2]))
    z.append(float(d[-1]))
  dis = numpy.zeros((len(x)-1,2))
  for i in range(1,len(x)):
    dis[i-1] = [numpy.sqrt((x[0]-x[i])**2+(y[0]-y[i])**2+(z[0]-z[i])**2),i]
    print dis[i-1]
  dis_min = []
  replace = []
  for i in range(1):
#    print i,len(dis),dis[0]
    dis_min = dis[0]
    for j in range(1,len(dis)-i):
#      dis_min = dis[j-1]
      if dis[j-1][0] < dis[j][0]:
        print "less"
        print dis[j-1],dis[j]
#        dis[j-1] = dis_min
        replace = 
        dis[j-1] = dis[j]
        print dis_min
#        #print replace
      elif dis_min[0] >= dis[j][0]:
        print "greater"
        print dis_min,dis[j],dis[j-1]
        replace = dis[j-1]
        dis[j-1] = dis[j]
        dis[j] = replace
#        dis_min = dis[j]
        print dis_min
  print "#######################################"
  for i in dis:
    print i
main()
