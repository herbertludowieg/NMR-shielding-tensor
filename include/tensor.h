#ifndef TENSOR_H
#define TENSOR_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include "linearalgebra.h"

class Tensor {
  public:
    Tensor();
    ~Tensor();
    void PI(double x) {pi=x;}
    void input_tensor ( std::ifstream & in );
    void print_tensor ( std::ostream & out , unsigned int a );
    double multiplication ( double x , double y , double z , 
                                                  unsigned int ten_fn);
    std::vector<double> linspace ( double start , double end , 
                                                         int total_points );
    void init_theta_phi ( int points );
    void points ( std::vector<double> coordinates , unsigned int ten_fn);

    double pi;
    
  private:
    std::vector<std::vector<std::vector<double> > > tensor_;
    //std::vector<std::vector<std::vector<std::vector<double> > > > point_coords_;
    std::vector<double> phi_,theta_;
};

#endif
