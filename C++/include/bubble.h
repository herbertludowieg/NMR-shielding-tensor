#ifndef BUBBLE_H
#define BUBBLE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

class Bubble {
  public:
    Bubble();
    ~Bubble();
    unsigned int file_size () { return coords_.size(); }
    bool input ( std::istream & in );
    void print ( std::ostream & out );
    void sort ( unsigned int atom );
    
  private:
    std::vector<std::string> info_;
    std::vector<std::vector<double> > coords_;
    std::vector<unsigned int> bonding_atoms_;
    //std::vector<std::vector<unsigned int> > distance_index_;
    //int cent_atom_;
    //std::vector<int> bond_atoms_;

};

#endif
