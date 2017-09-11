#include "bubble.h"

Bubble::Bubble() {}
Bubble::~Bubble() {}

/*bool Bubble::input ( std::istream & in ) {
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
}*/

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
  /*std::cout << "Organized data for atom 1" << std::endl;
  for ( unsigned int i = 0 ; i < distance.size() ; i++ ) {
    std::cout << distance[i] << ' ' << distance_index[i] << std::endl;
  }*/
  std::ofstream out_data_file;
  out_data_file.open("atom.bond.data",std::ios_base::app);
  out_data_file <<
  "-------------------" << std::endl << 
  std::setw(8) << " " << " | " << std::setw(8) << distance_index[0] << std::endl <<
  std::setw(8) << atom << " | " << std::setw(8) << distance_index[1] << std::endl <<
  std::setw(8) << " " << " | " << std::setw(8) << distance_index[2] << std::endl<<
  "-------------------" << std::endl;
  out_data_file.close();
  /*bonding_atoms_.push_back(atom);
  bonding_atoms_.push_back(distance_index[0]);
  bonding_atoms_.push_back(distance_index[1]);
  bonding_atoms_.push_back(distance_index[2]);*/
}
