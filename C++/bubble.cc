#include "bubble.h"

Bubble::Bubble() {}
Bubble::~Bubble() {}

bool Bubble::input ( std::istream & in ) {
  std::string line;
  std::getline(in,line);
  coords_.push_back(std::vector<double> ());
  if ( line[0] != 'C' or line[0] != ' ' ) {
    std::getline(in,line);
  } else if ( line[0] != 'C' and line[0] == ' ' ) {
    while ( line[0] == ' ' ) {
      std::getline(in,line,' ');
    }
  }
  info_.push_back(line);
  for ( int i ; i < 3 ; i++ ) {
    do {
      std::getline(in,line,' ');
    } while ( line[0] == ' ' );
    coords_[coords_.size()-1].push_back(std::atof(line.c_str()));
  }
  if ( line == "" ) {
    return false;
  } else {
    return true;
  }
}
