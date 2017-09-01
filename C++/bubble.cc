#include "bubble.h"

Bubble::Bubble() {}
Bubble::~Bubble() {}

bool Bubble::input ( std::istream & in ) {
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
  for ( unsigned int i = 0 ; i < coords_.size() ; i++ ) {
  std::cout << info_[i] << ' '
            << coords_[i][0] << ' ' 
            << coords_[i][1] << ' ' 
            << coords_[i][2] << std::endl;
  }
  if ( line == "" ) {
    return false;
  } else {
    return true;
  }
}
