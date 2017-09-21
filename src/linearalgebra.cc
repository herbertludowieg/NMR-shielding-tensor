#include "linearalgebra.h"

LinearAlgebra::LinearAlgebra() {}
LinearAlgebra::~LinearAlgebra() {}

double LinearAlgebra::signFunction ( double x ) {
  if ( x > 0. ) {
    return 1.;
  } else if ( x < 0. ) {
    return -1.;
  } else if ( x == 0. ) {
    return 0.;
  }
}

std::vector<std::vector<double> > LinearAlgebra::transpose ( 
                                 std::vector<std::vector<double> > matrix ) {
  std::vector<std::vector<double> > matrixt(matrix.size(),
                                         std::vector<double>(matrix[0].size()));
  for ( unsigned int i = 0 ; i < matrix.size() ; i++ ) {
    for ( unsigned int j = 0 ; j < matrix[i].size() ; j ++ ) {
      matrixt[i][j] = matrix[j][i];
    }
  }
  return matrixt;
}

std::vector<std::vector<double> > LinearAlgebra::dyadProduct ( 
                                                std::vector<double> a ,
                                                std::vector<double> b ) {
  std::vector<std::vector<double> > dyad;
  for ( unsigned int i = 0 ; i < a.size() ; i++ ) {
    dyad.push_back( std::vector<double> () );
    for ( unsigned int j = 0 ; j < b.size() ; j++ ) {
      dyad[i].push_back( a[i]*b[j] );
    }
  }
  return dyad;
}

double LinearAlgebra::dotProduct( std::vector<double> a , 
                                  std::vector<double> b ) {
  double dot;
  for ( unsigned int i = 0 ; i < a.size() ; i++ ) {
    //for ( unsigned int j = 0 ; j < b.size() ; j++ ) {
      //std::cout<<a[i]<<" "<<b[i]<<std::endl;
      dot = dot + a[i]*b[i];
    //}
  }
  return dot;
}

std::vector<std::vector<double> > LinearAlgebra::getIdentity ( int rows ) {
  std::vector<std::vector<double> > identity;
  for ( unsigned int i = 0 ; i < rows ; i++ ) {
    identity.push_back( std::vector<double> () );
    for ( unsigned int j = 0 ; j < rows ; j++ ) {
      if ( j == i ) {
        identity[i].push_back(1.);
      } else {
        identity[i].push_back(0.);
      }
    }
  }
  return identity;
}

std::vector<double> LinearAlgebra::multMatrix ( 
                                  std::vector<double> left,
                                  std::vector<double> right ) {
  std::vector<double> matrixmult ( left.size() );
  for ( unsigned int i = 0 ; i < left.size() ; i++ ) {
    matrixmult[i] = dotProduct(left,right);
  }
  return matrixmult;
}

void LinearAlgebra::print_matrix ( std::vector<std::vector<double> > a ) {
  std::cout << "Printing matrix" << std::endl;
  for ( unsigned int i = 0 ; i < a.size() ; i++ ) {
    for ( unsigned int j = 0 ; j < a[0].size() ; j++ ) {
      std::cout << std::setw(15) << a[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

std::vector<std::vector<double> > LinearAlgebra::householder ( 
                       std::vector<std::vector<double> > matrix ) {
  
  double alpha , r , tol = 1e-12;
  std::vector<double> w(matrix.size());
  std::vector<std::vector<double> > identity , 
    b_matrix(matrix.size(),std::vector<double>(matrix.size())) , dyad , 
    P(matrix.size(),std::vector<double>(matrix.size())) ,
    c_matrix(matrix.size(),std::vector<double>(matrix.size())); 
  unsigned int iteration , j , m;
  identity = getIdentity(matrix.size());
  b_matrix = matrix;
  for ( iteration = 0 ; iteration < b_matrix.size()-2 ; iteration++ ) {
    c_matrix = b_matrix;
    alpha = 0;
    for ( j = iteration+1 ; j < b_matrix.size() ; j++ ) {
      alpha = alpha + b_matrix[iteration][j]*b_matrix[iteration][j];
    }
    alpha = -signFunction(b_matrix[iteration+1][iteration])*std::sqrt(alpha);
    r = std::sqrt(0.5*alpha*alpha-0.5*b_matrix[iteration+1][iteration]*alpha);
    for ( j = 0 ; j < b_matrix.size() ; j++ ) {
      if ( j <= iteration ) {
        w[j] = 0;
      } else if ( j == iteration+1 ) {
        w[j] = (b_matrix[iteration][j]-alpha)/(2*r);
      } else {
        w[j] = (b_matrix[iteration][j])/(2*r);
      }
    }
    dyad = dyadProduct(w,w);
    //std::cout<<"Dyad"<<std::endl;
    //print_matrix(dyad);
    for ( j = 0 ; j < dyad.size() ; j++ ) {
      for ( m = 0 ; m < dyad[j].size() ; m++ ) {
        P[j][m] = identity[j][m]-2*dyad[j][m];
      }
    }
    //std::cout<<"P matrix"<<std::endl;
    //print_matrix(P);
    //std::cout<<"matrix before op"<<std::endl;
    //print_matrix(b_matrix);
    b_matrix = transpose(b_matrix);
    std::cout<<std::endl<<"New matrix products"<<std::endl;
    for ( j = 0 ; j < b_matrix.size() ; j++ ) {
      for ( m = 0 ; m < b_matrix.size() ; m++ ) {
        c_matrix[j][m] = dotProduct(P[j],b_matrix[m]);
        //std::cout << P[j][0] << " " << P[j][1] << " " << P[j][2] << " " 
        //          << std::endl;
        //std::cout << b_matrix[m][0] << " " << b_matrix[m][1] << " " << b_matrix[m][2] << " " 
        //          << std::endl;
        if ( std::abs(c_matrix[j][m]) <= tol ) {
          c_matrix[j][m] = 0.;
        }
      }
    }
    //print_matrix(c_matrix);
    P = transpose(P);
    for ( j = 0 ; j < b_matrix.size() ; j++ ) {
      for ( m = 0 ; m < b_matrix.size() ; m++ ) {
        b_matrix[j][m] = dotProduct(c_matrix[j],P[m]);
        if ( std::abs(b_matrix[j][m]) <= tol ) {
          b_matrix[j][m] = 0.;
        }
      }
    }
    //print_matrix(b_matrix);
  }
  return b_matrix;
}
