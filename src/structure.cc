#include "structure.h"

Structure::Structure () {}

Structure::~Structure () {}

// Will read the input file to get the coordinates in x,y,z directions.
void Structure::input_coord ( std::ifstream & in ) {
  std::string line;
  std::getline(in,line);
  while ( std::getline(in,line,' ') ) {
    coords_.push_back(std::vector<double> ());
    //info_.push_back(line);
    std::getline(in,line,' ');
    coords_[coords_.size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line,' ');
    coords_[coords_.size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line);
    coords_[coords_.size()-1].push_back( std::atof( line.c_str() ) );
  }
}

void Structure::print ( std::ostream & out ) {
  for ( unsigned int i = 0 ; i < coords_.size() ; i++ ) {
    out << coords_[i][0] << " " << coords_[i][1] << " " << coords_[i][2] 
        << std::endl;
  }
}

std::vector<double> Structure::get_coord ( unsigned int atom ) {
  return coords_[atom];
}
