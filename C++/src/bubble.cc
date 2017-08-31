#include "bubble.h"

Bubble::Bubble() {}
Bubble::~Bubble() {}

bool Bubble::input ( std::istream & in ) {
  std::string line;
  std::getline(in,line);
  info_.push_back( line );
  std::getline(in,line);
  coords_
}
