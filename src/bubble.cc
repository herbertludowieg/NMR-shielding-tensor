#include "bubble.h"

Bubble::Bubble() {}
Bubble::~Bubble() {}

std::vector<int> Bubble::sort ( unsigned int atom , 
                           std::vector<std::vector<double> > coords_) {
  std::vector<double> distance;
  std::vector<unsigned int> distance_index;
  double replace_dis = 0.;
  unsigned int replace_index = 0;
  for ( unsigned int i = 0 ; i < coords_.size() ; i++ ) {
    if ( i == atom ) {
      continue;
    }
    distance_index.push_back(i);
    distance.push_back( 
         std::sqrt(std::pow((coords_[atom][0]-coords_[i][0]),2) + 
                   std::pow((coords_[atom][1]-coords_[i][1]),2) +
                   std::pow((coords_[atom][2]-coords_[i][2]),2)));
  }
  for ( unsigned int i = 0 ; i < distance.size() ; i++ ) {
    for ( unsigned int j = 1 ; j < distance.size()-i ; j++ ) {
      replace_dis = 0.;
      replace_index = 0;
      if ( distance[j-1] < distance[j] ) {
        continue;
      } else if ( distance[j-1] >= distance[j] ) {
        replace_dis = distance[j-1];
        replace_index = distance_index[j-1];
        distance[j-1] = distance[j];
        distance_index[j-1] = distance_index[j];
        distance[j] = replace_dis;
        distance_index[j] = replace_index;
      }
    }
  }
  std::vector<int> bonds;
  bonds.push_back(atom);
  bonds.push_back(distance_index[0]);
  bonds.push_back(distance_index[1]);
  bonds.push_back(distance_index[2]);
  
  return bonds;
}
