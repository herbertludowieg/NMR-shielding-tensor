#include <iostream>
#include <string>
#include "bubble.h"
#include "tensor.h"
#include "structure.h"

int main( ) {
  Tensor tensor;
  Structure struc;
  unsigned int atom = 138;

  tensor.PI(3.14159265359);
  tensor.init_theta_phi(250);

  std::ifstream data;
  data.open("nanoccapped.xyz");
  struc.input_coord(data);
  data.close();
  //struc.print(std::cout);
  std::vector<double> coordinates;
  coordinates = struc.get_coord(atom);
  std::cout << coordinates[0] << " " << coordinates[1] << " " 
            << coordinates[2] << std::endl;

  data.open("tensor1.dat");
  tensor.input_tensor(data);
  data.close();
  tensor.points(coordinates);

  return 0;
}
