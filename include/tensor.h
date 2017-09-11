#ifndef TENSOR_H
#define TENSOR_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include "bubble.h"

class Tensor {
  public:
    Tensor();
    ~Tensor();
    unsigned int file_size () { return coords_.size(); }
    void input_coord ( std::ifstream & in );
    void input_tensor ( std::ifstream & in );
    double multiplication ( double x , double y , double z );
    std::vector<double> linspace ( double start , double end , 
                                                         int total_points );
    void points ();

    const double pi = 3.14159265359;
    
  private:
    std::vector<std::vector<double> > coords_ , tensor_;
    std::vector<std::vector<std::vector<double> > > point_coords_;
    std::vector<std::string> info_;
};

#endif
