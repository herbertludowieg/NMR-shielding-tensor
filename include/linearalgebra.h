#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <iostream>
#include <vector>
#include <cmath>

class LinearAlgebra {

  public:
    LinearAlgebra();
    ~LinearAlgebra();
    std::vector<std::vector<double> > transpose ( 
                               std::vector<std::vector<double> > matrix );
    std::vector<double> eigenvalues ( );
    std::vector<std::vector<double> > eigenvectors ();
    double determinant ( std::vector<std::vector<double> > matrix );
    std::vector<std::vector<double> > householder ( 
                           std::vector<std::vector<double> > matrix );
    std::vector<std::vector<double> > getIdentity ( int rows );
    std::vector<std::vector<double> > dyadProduct ( std::vector<double> a , 
                                                    std::vector<double> b );
    double dotProduct ( std::vector<double> a , std::vector<double> b );
    double signFunction ( double x );
    std::vector<std::vector<double> > multMatrix ( 
                           std::vector<std::vector<double> > left ,
                           std::vector<std::vector<double> > right );

};

#endif