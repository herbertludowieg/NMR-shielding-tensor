#include "tensor.h"

Tensor::Tensor() {}
Tensor::~Tensor(){}

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

void Tensor::input_tensor ( std::ifstream & in ) {
  std::string line;
  //std::getline(in,line);
  //std::cout << line << std::endl;
  while ( std::getline(in,line,' ') ) {
    std::cout << line << std::endl;
    tensor_.push_back( std::vector<double> () );
    tensor_[tensor_.size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line,' ');
    tensor_[tensor_.size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line,' ');
    tensor_[tensor_.size()-1].push_back( std::atof( line.c_str() ) );
  }
}

double Tensor::multiplication ( double x , double y , double z ) {
  //std::cout << tensor_.size() << " " << tensor_[0].size() << std::endl;
  return x*x*tensor_[0][0]+y*y*tensor_[1][1]+z*z*tensor_[2][2]+
         x*y*tensor_[0][1]+x*z*tensor_[0][2]+y*z*tensor_[1][2];
}

std::vector<double> Tensor::linspace ( double start , double end , 
                                                          int total_points) {
  std::vector<double> linear_space;
  for ( int i = 0 ; i < total_points ; i++ ) {
    linear_space.push_back( start + (double)i * (end-start) 
                                                     / (double)total_points);
  }
  return linear_space;
}

void Tensor::points ( ) {
  std::vector<double> phi,theta;
  std::vector<std::vector<double> > X,Y,Z,g;
  phi = linspace( 0.,pi,500 );
  theta = linspace( 0.,2*pi,500);
  for ( unsigned int i = 0 ; i < phi.size() ; i++ ) {
    X.push_back( std::vector<double> () );
    Y.push_back( std::vector<double> () );
    Z.push_back( std::vector<double> () );
    for ( unsigned int j = 0 ; j < theta.size() ; j++ ) {
      X[X.size()-1].push_back( std::sin(phi[i])*std::cos(theta[j]) );
      Y[Y.size()-1].push_back( std::sin(phi[i])*std::sin(theta[j]) );
      Z[Z.size()-1].push_back( std::cos(phi[i]) );
    }
  }
  /*for ( unsigned int i = 0 ; i < X.size() ; i++ ) {
    for ( unsigned int j = 0 ; j < X[0].size() ; j++ ) {
      std::cout << X[i][j] << " ";
    }
    std::cout << std::endl;
  }*/
  std::cout << X[0].size() << std::endl;
  std::cout << Y[0].size() << std::endl;
  std::cout << Z[0].size() << std::endl;
  //std::cout << multiplication(X[0][0],Y[0][0],Z[0][0]) << std::endl;
  for ( unsigned int i = 0 ; i < X.size() ; i++ ) {
    g.push_back( std::vector<double> () );
    //std::cout << i << std::endl;
    for ( unsigned int j = 0 ; j < X[0].size() ; j++ ) {
      //std::cout << j << std::endl;
      g[g.size()-1].push_back( multiplication( X[i][j],Y[i][j],Z[i][j] ) );
    }
  }
  std::cout << "g" << g.size() << g[0].size()<< std::endl;
  /*point_coords_.push_back(std::vector<std::vector<double> > (X.size(),
                                           std::vector<double> (X[0].size())));
  point_coords_.push_back(std::vector<std::vector<double> > (Y.size(),
                                           std::vector<double> (Y[0].size())));
  point_coords_.push_back(std::vector<std::vector<double> > (Z.size(),
                                           std::vector<double> (Z[0].size())));
  std::cout << point_coords_.size() << std::endl;*/
  
  for ( unsigned int i = 0 ; i < X.size() ; i++ ) {
    point_coords_.push_back( std::vector<std::vector<double> > () );
    point_coords_[i].push_back( std::vector<double> () );
    point_coords_[i].push_back( std::vector<double> () );
    point_coords_[i].push_back( std::vector<double> () );
    for ( unsigned int j = 0 ; j < X[0].size() ; j++ ) {
      point_coords_[i][0].push_back( g[i][j] * X[i][j] );
      point_coords_[i][1].push_back( g[i][j] * Y[i][j] );
      point_coords_[i][2].push_back( g[i][j] * Z[i][j] );
    }
  }
  std::cout << "here i am" << std::endl;
  /*for ( unsigned int i = 0 ; i < point_coords_.size() ; i++ ) {
    for ( unsigned int j = 0 ; j < point_coords_[0].size() ; j++ ) {
      std::cout << point_coords_[0][i][j] << std::endl;
    }
  }*/
  std::ofstream dat_out;
  dat_out.open("x.tensor.dat");
  dat_out << "#This file only has the x coordinate for the 3d plot" << std::endl;
  dat_out.close();
  dat_out.open("x.tensor.dat",std::ios_base::app);
  std::cout<<point_coords_.size() << " " << point_coords_[0].size() << 
             " " << point_coords_[0][0].size() << std::endl;
  for ( unsigned int i = 0 ; i < point_coords_.size() ; i++ ) {
    for ( unsigned int j = 0 ; j < point_coords_[i][0].size() ; j++ ) {
      dat_out << point_coords_[i][0][j] << " ";
    }
    dat_out << std::endl;
  }
  dat_out.close();
  //std::ofstream dat_out;
  dat_out.open("y.tensor.dat");
  dat_out << "#This file only has the y coordinate for the 3d plot" << std::endl
;
  dat_out.close();
  dat_out.open("y.tensor.dat",std::ios_base::app);
  for ( unsigned int i = 0 ; i < point_coords_.size() ; i++ ) {
    for ( unsigned int j = 0 ; j < point_coords_[i][0].size() ; j++ ) {
      dat_out << point_coords_[i][1][j] << " ";
    }
    dat_out << std::endl;
  }
  dat_out.close();
  //std::ofstream dat_out;
  dat_out.open("z.tensor.dat");
  dat_out << "#This file only has the z coordinate for the 3d plot" << std::endl
;
  dat_out.close();
  dat_out.open("z.tensor.dat",std::ios_base::app);
  for ( unsigned int i = 0 ; i < point_coords_.size() ; i++ ) {
    for ( unsigned int j = 0 ; j < point_coords_[i][0].size() ; j++ ) {
      dat_out << point_coords_[i][2][j] << " ";
    }
    dat_out << std::endl;
  }
  dat_out.close();
  Bubble bubble;
  unsigned int atom = 0 , max = coords_.size();
  while ( atom < max ) {
    bubble.sort( atom,coords_ );
    atom++;
  }
}
