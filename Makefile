CXX = g++
CFLAGS = -Wall -Iinclude/
BUILDDIR = build
SRCDIR = src
EXEC_SRC = src/main.cc
PYTHON = $(wildcard *.py)
SRCS = $(wildcard $(SRCDIR)/*.cc)
EXEC = main
DEP = $(patsubst $(SRCDIR)/%.cc,$(BUILDDIR)/%.o,$(SRCS))

all: execpy dir $(DEP) $(EXEC)

execpy: $(PYTHON)
	chmod +x $^

dir:
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR) $(EXEC) atom.bond.data xyz.tensor.dat
	chmod -x $(PYTHON)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
	$(CXX) $(CFLAGS) -c $^ -o $@

$(EXEC): $(DEP) $(EXEC_SRC)
	$(CXX) $(CFLAGS) $(DEP) -o $@
