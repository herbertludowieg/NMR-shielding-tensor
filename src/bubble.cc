#include "bubble.h"

Bubble::Bubble() {}
Bubble::~Bubble() {}

void Bubble::sort ( unsigned int atom , 
                           std::vector<std::vector<double> > coords_) {
  std::vector<double> distance;
  std::vector<unsigned int> distance_index;
  double replace_dis = 0.;
  unsigned int replace_index = 0;
  for ( unsigned int i = 0 ; i < coords_.size() ; i++ ) {
    if ( i == atom ) {
      i++;
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
  std::ofstream out_data_file;
  out_data_file.open("atom.bond.data",std::ios_base::app);
  out_data_file <<
  "-------------------" << std::endl << 
  std::setw(8) << " " << " | " << std::setw(8) << distance_index[0] << std::endl <<
  std::setw(8) << atom << " | " << std::setw(8) << distance_index[1] << std::endl <<
  std::setw(8) << " " << " | " << std::setw(8) << distance_index[2] << std::endl<<
  "-------------------" << std::endl;
  out_data_file.close();
}
