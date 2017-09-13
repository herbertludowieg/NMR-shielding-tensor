#include "tensor.h"

Tensor::Tensor() {}
Tensor::~Tensor(){}

// Will read the input file to get the coordinates in x,y,z directions.
void Tensor::input_coord ( std::ifstream & in ) {
  std::string line;
  std::getline(in,line);
  while ( std::getline(in,line,' ') ) {
    coords_.push_back(std::vector<double> ());
    info_.push_back(line);
    std::getline(in,line,' ');
    coords_[coords_.size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line,' ');
    coords_[coords_.size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line);
    coords_[coords_.size()-1].push_back( std::atof( line.c_str() ) );
  }
}

// Reads the input file that contains the tensor elements and stores them.
void Tensor::input_tensor ( std::ifstream & in ) {
  std::string line;
  while ( std::getline(in,line,' ') ) {
    tensor_.push_back( std::vector<double> () );
    tensor_[tensor_.size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line,' ');
    tensor_[tensor_.size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line,' ');
    tensor_[tensor_.size()-1].push_back( std::atof( line.c_str() ) );
  }
}

// Reduces the multiplication of the tensor with two vectors as 
//   described in the README.md file
double Tensor::multiplication ( double x , double y , double z ) {
  return x*x*tensor_[0][0]+y*y*tensor_[1][1]+z*z*tensor_[2][2]+
         x*y*tensor_[0][1]+x*z*tensor_[0][2]+y*z*tensor_[1][2];
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

void Tensor::points ( ) {
  std::vector<std::vector<double> > g;
  // creates a 4 dimension matrix
  point_coords_.push_back( std::vector<std::vector<std::vector<double> > > () );
  // it is important that phi and theta are same length so we can use
  // matplotlib to create the plot
  for ( unsigned int i = 0 ; i < phi_.size() ; i++ ) {
    point_coords_[0].push_back( std::vector<std::vector<double> > () );
    point_coords_[0].push_back( std::vector<std::vector<double> > () );
    point_coords_[0].push_back( std::vector<std::vector<double> > () );
    point_coords_[0][0].push_back( std::vector<double> () ); //x-coord
    point_coords_[0][1].push_back( std::vector<double> () ); //y-coord
    point_coords_[0][2].push_back( std::vector<double> () ); //z-coord
    for ( unsigned int j = 0 ; j < theta_.size() ; j++ ) {
      point_coords_[0][0][i].push_back( std::sin(phi_[i])*std::cos(theta_[j]) );
      point_coords_[0][1][i].push_back( std::sin(phi_[i])*std::sin(theta_[j]) );
      point_coords_[0][2][i].push_back( std::cos(phi_[i]) );
    }
  }
  //parameterization of r
  for ( unsigned int i = 0 ; i < point_coords_[0][0].size() ; i++ ) {
    g.push_back( std::vector<double> () );
    for ( unsigned int j = 0 ; j < point_coords_[0][0][0].size() ; j++ ) {
      g[i].push_back( multiplication( point_coords_[0][0][i][j],
                                      point_coords_[0][1][i][j],
                                      point_coords_[0][2][i][j] ) );
    }
  }
  //conversion back to cartesian
  for ( unsigned int i = 0 ; i < point_coords_[0][0].size() ; i++ ) {
    for ( unsigned int j = 0 ; j < point_coords_[0][0][0].size() ; j++ ) {
      point_coords_[0][0][i][j] = g[i][j] * point_coords_[0][0][i][j] ;
      point_coords_[0][1][i][j] = g[i][j] * point_coords_[0][1][i][j] ;
      point_coords_[0][2][i][j] = g[i][j] * point_coords_[0][2][i][j] ;
    }
  }
  //write to files
  std::ofstream dat_out;
  dat_out.open("x.tensor.dat");
  dat_out << "#This file only has the x coordinate for the 3d plot" << std::endl;
  dat_out.close();
  dat_out.open("x.tensor.dat",std::ios_base::app);
  for ( unsigned int i = 0 ; i < point_coords_[0][0].size() ; i++ ) {
    for ( unsigned int j = 0 ; j < point_coords_[0][0][i].size() ; j++ ) {
      dat_out << point_coords_[0][0][i][j] << " ";
    }
    dat_out << std::endl;
  }
  dat_out.close();
  dat_out.open("y.tensor.dat");
  dat_out << "#This file only has the y coordinate for the 3d plot" << std::endl
;
  dat_out.close();
  dat_out.open("y.tensor.dat",std::ios_base::app);
  for ( unsigned int i = 0 ; i < point_coords_[0][1].size() ; i++ ) {
    for ( unsigned int j = 0 ; j < point_coords_[0][1][i].size() ; j++ ) {
      dat_out << point_coords_[0][1][i][j] << " ";
    }
    dat_out << std::endl;
  }
  dat_out.close();
  dat_out.open("z.tensor.dat");
  dat_out << "#This file only has the z coordinate for the 3d plot" << std::endl
;
  dat_out.close();

  dat_out.open("z.tensor.dat",std::ios_base::app);
  for ( unsigned int i = 0 ; i < point_coords_[0][2].size() ; i++ ) {
    for ( unsigned int j = 0 ; j < point_coords_[0][2][i].size() ; j++ ) {
      dat_out << point_coords_[0][2][i][j] << " ";
    }
    dat_out << std::endl;
  }
  dat_out.close();
  //this will be used later to help with plotting the structure
  Bubble bubble;

  unsigned int atom = 0 , max = coords_.size();

  while ( atom < max-1 ) {
    bubble.sort( atom,coords_ );
    atom++;
  }
}
