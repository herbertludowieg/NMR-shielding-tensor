#include <iostream>
#include <string>
#include "bubble.h"
#include "tensor.h"

int main( ) {
  std::ofstream out_data_file;
  out_data_file.open("atom.bond.data");
  out_data_file << 
  "# This file will contain the organized data for the molecule" << std::endl <<
  "# with the indeces of the closes bonding atoms and the central" << std::endl <<
  "# atom to which they bond to. This is done with the assumption" << std::endl <<
  "# of how many atoms will bond together. This will probably" << std::endl << 
  "# change to make the program more general." << std::endl <<
  "# The file format is as follows" << std::endl <<
  "#              | Bond atom " << std::endl <<
  "# Central atom | Bond atom " << std::endl <<
  "#              | Bond atom " << std::endl;
  out_data_file.close();
  //unsigned int atom = 0 , size;
  Bubble bubble;
  Tensor tensor;
  tensor.PI(3.14159265359);
  tensor.init_theta_phi(5000);
  std::ifstream data;
  data.open("nanoccapped.xyz");
  tensor.input_coord(data);
  data.close();
  std::ifstream tensor_dat;
  tensor_dat.open("tensor1.dat");
  tensor.input_tensor(tensor_dat);
  tensor_dat.close();
  /*size = tensor.file_size()-1;
  while ( atom < size ) {
    bubble.sort(atom);
    atom++;
  }*/
  tensor.points();
  return 0;
}
