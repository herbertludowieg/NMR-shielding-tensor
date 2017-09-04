CXX = g++
CFLAGS = -Wall
BUILDDIR = ./build/
EXEC_SRC = main.cc
SRCS := $(wildcard *.cc)
SRCS := $(filter-out $(EXEC_SRC),$(SRCS))
EXEC = main
DEP = $(SRCS:.cc=.o)

all: $(DEP) $(EXEC)

clean:
	rm -rf *.o $(EXEC) atom.bond.data

$(DEP): $(SRCS)
	$(CXX) $(CFLAGS) -c $^ -o $@

$(EXEC): $(DEP) $(EXEC_SRC)
	$(CXX) $(CFLAGS) $(DEP) -o $@ $(EXEC_SRC)
