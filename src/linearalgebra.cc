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
    for ( unsigned int j = 0 ; j < b.size() ; j++ ) {
      dot = dot + a[i]*b[i];
    }
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

std::vector<std::vector<double> > LinearAlgebra::multMatrix ( 
                                  std::vector<std::vector<double> > left,
                                  std::vector<std::vector<double> > right ) {
  std::vector<std::vector<double> > matrixmult (
               left.size(),std::vector<double> (right.size()));
  right = transpose(right);
  for ( unsigned int i = 0 ; i < left.size() ; i++ ) {
    for ( unsigned int j = 0 ; j < right.size() ; j++ ) {
      matrixmult[i][j] = dotProduct(left[j],right[i]);
    }
  }
  return matrixmult;
}

std::vector<std::vector<double> > LinearAlgebra::householder ( 
                       std::vector<std::vector<double> > matrix ) {
  
  double alpha , r;
  std::vector<double> w(matrix.size());
  std::vector<std::vector<double> > identity , 
    b_matrix(matrix.size(),std::vector<double>(matrix.size())) , dyad , 
    P(matrix.size(),std::vector<double>(matrix.size()));
  unsigned int iteration , j , m;
  identity = getIdentity(matrix.size());
  b_matrix = matrix;
  for ( iteration = 0 ; iteration < matrix.size()-1 ; iteration++ ) {
    alpha = 0;
    for ( j = iteration+1 ; j < matrix.size() ; j++ ) {
      alpha = alpha + matrix[iteration][j]*matrix[iteration][j];
    }
    alpha = -signFunction(matrix[iteration+1][iteration])*std::sqrt(alpha);
    r = std::sqrt(0.5*alpha*alpha-0.5*matrix[iteration+1][iteration]*alpha);
    for ( j = 0 ; j < matrix.size() ; j++ ) {
      if ( j <= iteration ) {
        w[j] = 0;
      } else if ( j == iteration+1 ) {
        w[j] = (matrix[iteration][iteration+1]-alpha)/(2*r);
      }
    }
    dyad = dyadProduct(w,w);
    for ( j = 0 ; j < dyad.size() ; j++ ) {
      for ( m = 0 ; m < dyad[j].size() ; m++ ) {
        P[j][m] = identity[j][m]-2*dyad[j][m];
      }
    }
    b_matrix = multMatrix(P,b_matrix);
    b_matrix = multMatrix(b_matrix,P);
  }
  return b_matrix;
}
