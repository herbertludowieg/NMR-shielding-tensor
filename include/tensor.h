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
    void PI(double x) {pi=x;}
    void input_tensor ( std::ifstream & in );
    double multiplication ( double x , double y , double z );
    std::vector<double> linspace ( double start , double end , 
                                                         int total_points );
    void init_theta_phi ( int points );
    void points ( std::vector<double> coordinates );

    double pi;
    
  private:
    std::vector<std::vector<double> > tensor_;
    std::vector<std::vector<std::vector<std::vector<double> > > > point_coords_;
    std::vector<double> phi_,theta_;
};

#endif
