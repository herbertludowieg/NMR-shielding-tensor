#ifndef BUBBLE_H
#define BUBBLE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

class Bubble {
  public:
    Bubble();
    ~Bubble();
    bool input ( std::istream & in );
    void print ( std::ostream & out );
    void sort ( );
    
  private:
    std::vector<std::string> info_;
    std::vector<std::vector<double> > coords_ , distance_;
    std::vector<std::vector<unsigned int> > distance_index_;
    //int cent_atom_;
    //std::vector<int> bond_atoms_;

};

#endif
