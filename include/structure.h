#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "bubble.h"

class Structure {
  public:
    Structure ();
    ~Structure ();
    void input_coord ( std::ifstream & in );
    void print ( std::ostream & out );
    std::vector<double> get_coord ( unsigned int atom );

  private:
    std::vector<std::vector<double> > coords_;

};

#endif
