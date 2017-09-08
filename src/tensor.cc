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
  std::getline(in,line);
  while ( std::getline(in,line,' ') ) {
    tensor_.push_back( std::vector<double> () );
    tensor_[tensor.size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line,' ');
    tensor_[tensor.size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line,' ');
    tensor_[tensor.size()-1].push_back( std::atof( line.c_str() ) );
  }
}


