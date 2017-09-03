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
  if ( line == "" ) {
    return false;
  } else {
    return true;
  }
}

void Bubble::print ( std::ostream & out ) {
  out << "Inputted data" << std::endl;
  for ( unsigned int i = 0 ; i < coords_.size() ; i++ ) {
    out << info_[i] << ' '
        << coords_[i][0] << ' '
        << coords_[i][1] << ' '
        << coords_[i][2] << std::endl;
  }
}

void Bubble::sort () {
  //std::vector<std::vector<double> > distance;
  //std::vecotr<std::vector<unsigned int> > distance_index;
  for ( unsigned int center = 0 ; center < 1 ; center++ ) {
    distance_.push_back(std::vector<double> () );
    distance_index_.push_back(std::vector<unsigned int> () );
    for ( unsigned int i = 0 ; i < coords_.size() ; i++ ) {
      if ( i == center ) {
        i++
      }
      distance_index_[center].push_back(i);
      distance_[center].push_back( 
           std::sqrt(std::pow((coords_[center][0]-coords_[i][0]),2) + 
                     std::pow((coords_[center][1]-coords_[i][1]),2) +
                     std::pow((coords_[center][2]-coords_[i][2]),2))
    }
  }
}
