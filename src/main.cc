#include <iostream>
#include <string>
#include "tensor.h"
#include "structure.h"

int main( ) {
  Tensor tensor;
  Structure struc;
  bool coord_found = false;
  std::string coord_file , line;
  while ( !coord_found ) {
    std::cout << "Enter location of coordinate file: ";
    std::getline(std::cin,line);
    if ( line == "exit" ) {
      return 0;
    }
    if ( !std::ifstream(line.c_str()) ){
      std::cout << "ERROR:" << std::endl;
      std::cout << "\tFile "<<line<<" does not exist"<<std::endl;
      std::cout << "\tRe-enter filename" << std::endl;
      std::cout << "\tOr enter exit to quit" << std::endl;
      coord_found = false;
    } else {
      coord_found = true;
      coord_file = line;
    }
  }
  std::ifstream data;
  data.open(coord_file.c_str());
  struc.input_coord(data);
  data.close();
  unsigned int data_size = struc.coord_size();
  unsigned int number;
  std::cout << "Enter the number of tensors to be plotted: ";
  std::cin >> number;
  std::vector<unsigned int> atom(number);
  std::vector<std::string> files;
  std::cin.ignore();
  for ( unsigned int i = 0 ; i < number ; i++ ) {
    std::cout << "Enter tensor file " << i+1 << ": ";
    std::getline(std::cin,line);
    if ( line == "exit" ) {
      return 0;
    }
    if ( !std::ifstream(line.c_str()) ){
      std::cout << "ERROR:" << std::endl;
      std::cout << "\tFile "<<line<<" does not exist"<<std::endl;
      std::cout << "\tRe-enter filename" << std::endl;
      std::cout << "\tOr enter exit to quit" << std::endl;
      i--;
      continue;
    }
    files.push_back(line);
  }

  for ( unsigned int i = 0 ; i < number ; i++ ) {
    std::cout << "Enter the atom to apply "<<files[i]<<" to: ";
    std::getline(std::cin,line);
    if ( line == "exit" ) {
      return 0;
    }
    if ( std::atoi(line.c_str()) > (int)data_size ) {
      std::cout << "ERROR:" << std::endl;
      std::cout << "\tThe atom you are looking for does not exist"<<std::endl
                << "\tin the data set of "<<coord_file<<std::endl
                << "\tcontaining "<<data_size<<" data points."<<std::endl
                << "\tRe-enter the value" << std::endl
                << "\tOr enter exit to quit"<<std::endl;
      i--;
      continue;
    }
    atom[i] = (unsigned int)std::atoi(line.c_str())-1;
  }
  
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
  
  /*std::ifstream data;
  data.open("nanoccapped.xyz");
  struc.input_coord(data);
  data.close();*/
  struc.print(std::cout);
  for ( unsigned int i = 0 ; i < number ; i++ ) {
    //std::cout << files[i] << std::endl;
    std::vector<double> coordinates;
    coordinates = struc.get_coord(atom[i]);
    data.open(files[i].c_str());
    tensor.input_tensor(data);
    std::cout << "Printing inputted tensor "<<i+1<<std::endl;
    tensor.print_tensor(std::cout,i);
    data.close();
    tensor.points(coordinates,i);
  }
  return 0;
}
