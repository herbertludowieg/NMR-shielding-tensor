#include <iostream>
#include <string>
#include "tensor.h"
#include "structure.h"

int main( ) {
  Tensor tensor;
  Structure struc;
  unsigned int number = 2;
  unsigned int atom[] = {138,57};
  char files[2][15] = {"tensor1.dat","tensor2.dat"};
  std::ofstream dat_out;
  
  tensor.PI(3.14159265359);
  tensor.init_theta_phi(250);

  dat_out.open("x.tensor.dat");
  dat_out << "#This file only has the x coordinate for the 3d plot" << std::endl
;
  dat_out.close();
  dat_out.open("y.tensor.dat");
  dat_out << "#This file only has the y coordinate for the 3d plot" << std::endl
;
  dat_out.close();
  dat_out.open("z.tensor.dat");
  dat_out << "#This file only has the z coordinate for the 3d plot" << std::endl
;
  dat_out.close();
  
  std::ifstream data;
  data.open("nanoccapped.xyz");
  struc.input_coord(data);
  data.close();
  struc.print(std::cout);
  for ( unsigned int i = 0 ; i < number ; i++ ) {
    std::cout << files[i] << std::endl;
    std::vector<double> coordinates;
    coordinates = struc.get_coord(atom[i]);
    data.open(files[i]);
    tensor.input_tensor(data);
    std::cout << "Printing inputted tensor "<<i+1<<std::endl;
    tensor.print_tensor(std::cout,i);
    data.close();
    tensor.points(coordinates,i);
  }
  return 0;
}
