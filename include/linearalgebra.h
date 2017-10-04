#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

class LinearAlgebra {

  public:
    LinearAlgebra();
    ~LinearAlgebra();
    void print_matrix ( std::vector<std::vector<double> > a );
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
    std::vector<double> multMatrix ( 
                           std::vector<double> left ,
                           std::vector<double> right );
    std::vector<std::vector<double> > qrMethod ( 
<<<<<<< HEAD
                           std::vector<std::vector<double> > matrix );
    bool upperTriangular ( std::vector<std::vector<double> > matrix );
=======
                              std::vector<std::vector<double> > matrix );
>>>>>>> 00f4e914551bfa0ef3697be91f14e8560484e53f

};

#endif
