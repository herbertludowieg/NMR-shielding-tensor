#include "linearalgebra.h"

LinearAlgebra::LinearAlgebra() {}
LinearAlgebra::~LinearAlgebra() {}

std::vector<double> LinearAlgebra::eigenvalues ( 
                                  std::vector<std::vector<double> > matrix ) {
  std::vector<double> values(matrix.size());
  matrix = householder(matrix);
  matrix = qrMethod(matrix);
  for ( unsigned int i = 0 ; i < matrix.size() ; i++ ) {
    values[i] = matrix[i][i];
  }
  return values;
}

double LinearAlgebra::signFunction ( double x ) {
  if ( x > 0. ) {
    return 1.;
  } else if ( x < 0. ) {
    return -1.;
  } else {
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
  double dot = 0.;
  for ( unsigned int i = 0 ; i < a.size() ; i++ ) {
    dot = dot + a[i]*b[i];
  }
  return dot;
}

std::vector<std::vector<double> > LinearAlgebra::getIdentity ( int rows ) {
  std::vector<std::vector<double> > identity;
  for ( unsigned int i = 0 ; (int)i < rows ; i++ ) {
    identity.push_back( std::vector<double> () );
    for ( unsigned int j = 0 ; (int)j < rows ; j++ ) {
      if ( j == i ) {
        identity[i].push_back(1.);
      } else {
        identity[i].push_back(0.);
      }
    }
  }
  return identity;
}

/*bool LinearAlgebra::upperTriangular ( 
                         std::vector<std::vector<double> > matrix ) {
  double tol = 1e-12 , sum;
  for ( unsigned int i = 0 ; i < matrix.size()-1 ; i++ ) {
    sum = 0.;
    for ( unsigned int k = i+1 ; k < matrix[i].size() ; k++ ) {
      sum = sum + matrix[k][i];
    }
    if ( sum >= tol ) {
      std::cout << "Matrix is not yet diagonal" << std::endl;
      return false;
    }
  }
  std::cout << "Matrix is diagonal" << std::endl;
  return true;
}*/

void LinearAlgebra::print_matrix ( std::vector<std::vector<double> > a ) {
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
    for ( j = 0 ; j < dyad.size() ; j++ ) {
      for ( m = 0 ; m < dyad[j].size() ; m++ ) {
        P[j][m] = identity[j][m]-2*dyad[j][m];
      }
    }
    b_matrix = transpose(b_matrix);
    for ( j = 0 ; j < b_matrix.size() ; j++ ) {
      for ( m = 0 ; m < b_matrix.size() ; m++ ) {
        c_matrix[j][m] = dotProduct(P[j],b_matrix[m]);
        if ( std::abs(c_matrix[j][m]) <= tol ) {
          c_matrix[j][m] = 0.;
        }
      }
    }
    P = transpose(P);
    for ( j = 0 ; j < b_matrix.size() ; j++ ) {
      for ( m = 0 ; m < b_matrix.size() ; m++ ) {
        b_matrix[j][m] = dotProduct(c_matrix[j],P[m]);
        if ( std::abs(b_matrix[j][m]) <= tol ) {
          b_matrix[j][m] = 0.;
        }
      }
    }
  }
  std::cout << "Matrix after Householder method:" << std::endl;
  print_matrix(b_matrix);
  return b_matrix;
}

std::vector<std::vector<double> > LinearAlgebra::qrMethod (
                       std::vector<std::vector<double> > matrix ) {
  double tol , angle;
  std::vector<std::vector<double> > A=matrix , 
        P(matrix.size(),std::vector<double> (matrix.size())) , 
        Q(matrix.size(),std::vector<double> (matrix.size())) , 
        R(matrix.size(),std::vector<double> (matrix.size())) , 
        L(matrix.size(),std::vector<double> (matrix.size())) , 
        B(matrix.size(),std::vector<double> (matrix.size())) ;
  unsigned int iter=0 , i , k , j;
  for ( i = 1 ; i < matrix.size() ; i++ ) {
    for ( k = 0 ; k < i ; k++ ) {
      tol = tol + A[i][k];
    }
  }
  std::cout << "Sum of elements below diagonal iteration " << iter << ":"
            << tol << std::endl;
  while ( std::abs(tol) > 1e-12 ) {
    tol = 0;
    R = A;
    for ( i = 0 ; i < matrix.size()-1 ; i++ ) {
      P = getIdentity((int)matrix.size());
      for ( k = 0 ; k < matrix.size() ; k++ ) {
        if ( k < i ) {
          continue;
        } else if ( k == i ) {
          angle = std::atan2(R[k+1][k],R[k][k]);
          P[k][k] = std::cos(angle);
          P[k+1][k] = -std::sin(angle);
          P[k][k+1] = std::sin(angle);
          P[k+1][k+1] = std::cos(angle);
        } else if ( k >= i+1 ) {
          continue;
        }
      }
      R = transpose(R);
      for ( k = 0 ; k < matrix.size() ; k++ ) {
        for ( j = 0 ; j < matrix.size() ; j++ ) {
          B[k][j] = dotProduct(P[k],R[j]);
        }
      }
      R = B;
      if ( i == 0 ) {
        Q = transpose(P);
      } else {
        L = Q;
        for ( k = 0 ; k < matrix.size() ; k++ ) {
          for ( j = 0 ; j < matrix.size() ; j++ ) {
            Q[k][j] = dotProduct(L[k],P[j]);
          }
        }
      }
    }
    Q = transpose(Q);
    for ( k = 0 ; k < matrix.size() ; k++ ) {
      for ( j = 0 ; j < matrix.size() ; j++ ) {
        A[k][j] = dotProduct(R[k],Q[j]);
      }
    }
    for ( i = 1 ; i < matrix.size() ; i++ ) {
      for ( k = 0 ; k < i ; k++ ) {
        tol = tol + A[i][k];
      }
    }
    iter++;
    std::cout << "Sum of elements below diagonal iteration " << iter << ":"
              << tol << std::endl;

  }
  std::cout << "Matrix after QR method:" << std::endl;
  print_matrix(A);
  return A;
}
