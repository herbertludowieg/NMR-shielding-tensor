#include "structure.h"

Structure::Structure () {}

Structure::~Structure () {}

// Will read the input file to get the coordinates in x,y,z directions.
void Structure::input_coord ( std::ifstream & in ) {
  std::string line;
  std::getline(in,line);
  while ( std::getline(in,line,' ') ) {
    coords_.push_back(std::vector<double> ());
    std::getline(in,line,' ');
    coords_[coords_.size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line,' ');
    coords_[coords_.size()-1].push_back( std::atof( line.c_str() ) );
    std::getline(in,line);
    coords_[coords_.size()-1].push_back( std::atof( line.c_str() ) );
  }
}

void Structure::print ( std::ostream & out ) {
  std::ofstream data;
  data.open("coordinates.structure.dat");
  data.close();
  data.open("coordinates.structure.dat",std::ios_base::app);
  for ( unsigned int i = 0 ; i < coords_.size() ; i++ ) {
    data << coords_[i][0] << " " << coords_[i][1] << " " << coords_[i][2] 
        << std::endl;
  }
  data.close();
  std::vector<int> x;
  std::vector<std::vector<int> > bonds;
  Bubble bubble;
  for ( unsigned int atom = 0 ; atom < coords_.size() ; atom++ ) {
    std::cout<<atom<<std::endl;
    bonds.push_back( std::vector<int> () );
    x = bubble.sort(atom,coords_);
    for ( unsigned int i = 0 ; i < x.size() ; i++ ) {
      bonds[atom].push_back( x[i] );
    }
  }
  for ( unsigned int i = 0 ; i < bonds.size() ; i++ ) {
    int compare = bonds[i][0];
    //std::cout<<i<<std::endl;
    for ( unsigned int j = 1 ; j < bonds[i].size() ; j++ ) {
      if ( bonds[i][j] == -1 ) {
        continue;
      } else {
        for ( unsigned int k = 0 ; k < bonds[(unsigned int)bonds[i][j]].size()
              ; ++k ) {
          if ( compare == bonds[(unsigned int)bonds[i][j]][k] ) {
            bonds[(unsigned int)bonds[i][j]][k] = -1;
            break;
          }
        }
      }
    }
  }
  data.open("sorted.structure.dat");
  data.close();
  data.open("sorted.structure.dat",std::ios_base::app);
  for ( unsigned int i = 0 ; i < bonds.size() ; i++ ) {
    for ( unsigned int j = 0 ; j < bonds[i].size() ; j++ ) {
      data << bonds[i][j] << " ";
      
    }
    data << std::endl;
  }
}

std::vector<double> Structure::get_coord ( unsigned int atom ) {
  return coords_[atom];
}
