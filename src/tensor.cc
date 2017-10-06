#include "tensor.h"

Tensor::Tensor() {}
Tensor::~Tensor(){}

// Reads the input file that contains the tensor elements and stores them.
void Tensor::input_tensor ( std::ifstream & in ) {
  tensor_.push_back(std::vector<std::vector<double> > () );
  std::string line;
  unsigned int a = tensor_.size()-1;
  while ( std::getline(in,line,' ') ) {
    tensor_[a].push_back( std::vector<double> () );
    tensor_[a][tensor_[a].size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line,' ');
    tensor_[a][tensor_[a].size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line);
    tensor_[a][tensor_[a].size()-1].push_back( std::atof( line.c_str() ) );
  }
}

// Prints the tensor data in a formatted structure
void Tensor::print_tensor ( std::ostream & out , unsigned int a ) {
  for ( unsigned int i = 0 ; i < tensor_[a].size() ; i++ ) {
    for ( unsigned int j = 0 ; j < tensor_[a][i].size() ; j++ ) {
      out << std::setw(8) << tensor_[a][i][j] << " ";
    }
    out << std::endl;
  }
}

// Tensor multiplication as described in original program
double Tensor::multiplication ( double x , double y , double z , 
                                                      unsigned int ten_fn ) {
  return (x*x*tensor_[ten_fn][0][0]+y*y*tensor_[ten_fn][1][1]+
          z*z*tensor_[ten_fn][2][2]+2*x*y*tensor_[ten_fn][0][1]+
          2*x*z*tensor_[ten_fn][0][2]+2*y*z*tensor_[ten_fn][1][2])*0.03;
}

// A function that copies the numpy.linspace function in Python
std::vector<double> Tensor::linspace ( double start , double end , 
                                                          int total_points) {
  std::vector<double> linear_space;
  for ( int i = 0 ; i < total_points ; i++ ) {
    linear_space.push_back( start + (double)i * (end-start) 
                                                     / (double)total_points);
  }
  return linear_space;
}

// Initialize theta and phi variables to not eat up more computation power
//   when calculating multiple tensors
void Tensor::init_theta_phi ( int points ) {
  phi_ = linspace( 0. , pi , points );
  theta_ = linspace ( 0. , 2.*pi , points );
}

void Tensor::points ( std::vector<double> coordinates , unsigned int ten_fn ) {
  std::vector<std::vector<double> > g;
  std::vector<std::vector<std::vector<double> > > point_coords_;
  // it is important that phi and theta are same length so we can use
  // matplotlib to create the plot
  point_coords_.push_back( std::vector<std::vector<double> > () );
  point_coords_.push_back( std::vector<std::vector<double> > () );
  point_coords_.push_back( std::vector<std::vector<double> > () );
  for ( unsigned int i = 0 ; i < phi_.size() ; i++ ) {
    point_coords_[0].push_back( std::vector<double> () ); //x-coord
    point_coords_[1].push_back( std::vector<double> () ); //y-coord
    point_coords_[2].push_back( std::vector<double> () ); //z-coord
    for ( unsigned int j = 0 ; j < theta_.size() ; j++ ) {
      //x-coord in spherical
      point_coords_[0][i].push_back( std::sin(phi_[i])*std::cos(theta_[j]) );
      //y-coord in spherical
      point_coords_[1][i].push_back( std::sin(phi_[i])*std::sin(theta_[j]) );
      //z-coord in spherical
      //  could optimize code here to only calculate a column vector of 
      //  z-coord points
      point_coords_[2][i].push_back( std::cos(phi_[i]) );
    }
  }
  //parameterization of r
  for ( unsigned int i = 0 ; i < point_coords_[0].size() ; i++ ) {
    g.push_back( std::vector<double> () );
    for ( unsigned int j = 0 ; j < point_coords_[0][0].size() ; j++ ) {
      g[i].push_back( multiplication( point_coords_[0][i][j] ,
                                      point_coords_[1][i][j] ,
                                      point_coords_[2][i][j] ,
                                      ten_fn ) );
    }
  }
  //conversion back to cartesian
  for ( unsigned int i = 0 ; i < point_coords_[0].size() ; i++ ) {
    for ( unsigned int j = 0 ; j < point_coords_[0][0].size() ; j++ ) {
      //x-coord cartesian
      point_coords_[0][i][j] = g[i][j] * point_coords_[0][i][j] 
                                              + coordinates[0];
      //y-coord cartesian
      point_coords_[1][i][j] = g[i][j] * point_coords_[1][i][j]
                                              + coordinates[1];
      //z-coord cartesian
      point_coords_[2][i][j] = g[i][j] * point_coords_[2][i][j]
                                              + coordinates[2];
    }
  }
  //write to files
  std::ofstream dat_out;

  dat_out.open("x.tensor.dat",std::ios_base::app);
  for ( unsigned int i = 0 ; i < point_coords_[0].size() ; i++ ) {
    for ( unsigned int j = 0 ; j < point_coords_[0][i].size() ; j++ ) {
      dat_out << point_coords_[0][i][j] << " ";
    }
    dat_out << std::endl;
  }
  dat_out.close();

  dat_out.open("y.tensor.dat",std::ios_base::app);
  for ( unsigned int i = 0 ; i < point_coords_[1].size() ; i++ ) {
    for ( unsigned int j = 0 ; j < point_coords_[1][i].size() ; j++ ) {
      dat_out << point_coords_[1][i][j] << " ";
    }
    dat_out << std::endl;
  }
  dat_out.close();

  dat_out.open("z.tensor.dat",std::ios_base::app);
  for ( unsigned int i = 0 ; i < point_coords_[2].size() ; i++ ) {
    for ( unsigned int j = 0 ; j < point_coords_[2][i].size() ; j++ ) {
      dat_out << point_coords_[2][i][j] << " ";
    }
    dat_out << std::endl;
  }
  dat_out.close();
  LinearAlgebra linear;
  //double a[] = {4,1,-2,2},b[] = {1,2,0,1},c[] = {-2,0,3,-2},d[] = {2,1,-2,-1};
  //double a[] = {3,1,0},b[]={1,3,1},c[]={0,1,3};
  /*std::vector<std::vector<double> > matrix(3,std::vector<double>(3));
  
  for ( unsigned int i = 0 ; i < matrix.size() ; i++ ) {
    matrix[0][i] = a[i];
    matrix[1][i] = b[i];
    matrix[2][i] = c[i];
    //matrix[3][i] = d[i];
  }*/
  std::vector<double> e_values;
  e_values = linear.eigenvalues(tensor_[ten_fn]);
  /*similaritytrans = linear.householder(matrix);
  similaritytrans = linear.qrMethod(matrix);*/
  //std::cout << "Matrix after Householder's method"<<std::endl;
  std::cout << "==================================================" 
            << std::endl << "Eigenvalues:" << std::endl;
  for ( unsigned int i = 0 ; i < e_values.size() ; i++ ) {
      std::cout << std::setw(8) << e_values[i] << " ";
  }
  std::cout<<std::endl;
}
