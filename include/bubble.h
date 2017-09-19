#ifndef BUBBLE_H
#define BUBBLE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

class Bubble {
  public:
    Bubble();
    ~Bubble();
    std::vector<int> sort ( unsigned int atom , 
                               std::vector<std::vector<double> > coords_ );
};

#endif
