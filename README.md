# NMR-shielding-tensor
-----------------------------------ABOUT----------------------------------------
This program is an open source version of a script created by Dr. Jochen 
Autschbach from the University at Buffalo. The original version of the program 
can be found in the link below.
<http://ja01.chem.buffalo.edu/~jochena/tutorials/tutorials.html>

-------------------------------REQUIREMENTS-------------------------------------
The requirements for this program are as follows:
	Make
	C++ compiler
	Python 2.x

--------------------------------COMPILING---------------------------------------
To compile the code a Makefile has been provided with some preset values for 
compiling C++ code with the g++ compiler. It will create a main executable on 
the same directory as the Makefile. 
There also exists a function in the Makefile to allow the .py files to run as 
an executable. To do this type
$ make execpy
and it will add executable permissions to all .py files on the directory.
Running the clean function for make will erase all files created by the program.

---------------------------RUNNING THE PROGRAM----------------------------------
To execute the program run the main executable which will write all of the data 
to pre-determined files.
To plot the structure run the python script read_structure.py. The code was 
tested with matplotlib 0.99, 1.1 and 1.5.1. Ran well on all versions mentioned.

-------------------------------LIMITATIONS--------------------------------------
This should just serve as a friendly reminder; it has been harcoded into 
the program that for the tensor a 250x250 matrix of doubles is being calculated 
for each x, y and z coordinate. It was tested for a single tensor with n=5000
matrices and the C++ code was able to complete utilizing about 1GB of RAM.
However, python would not be able to plot the data before running out of 
memory.

-----------------------------ACKNOWLEDGEMENTS-----------------------------------
[1] Zurek, E.; Pickard, C.; Autschbach, J., 'A Density Functional Study of the 
    13C NMR Chemical Shifts in Single-Walled Carbon Nanotubes with Stone-Wales
    Defects', J. Phys. Chem. C 2008, 112, 11744-11750. 
    URL: <http://dx.doi.org/10.1021/jp803180v>

[2] Autschbach, J.; Zheng, S.; Schurko, R. W., 'Analysis of Electric Field 
    Gradient Tensors at Quadrupolar Nuclei in Common Structural Motifs', 
    Concepts Magn. Reson. A 2010, 36A, 84-126.
    URL: <http://dx.doi.org/10.1002/cmr.a.20155>
