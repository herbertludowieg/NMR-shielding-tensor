CXX = g++
CFLAGS = -Wall -Iinclude/
BUILDDIR = build
SRCDIR = src
EXEC_SRC = src/main.cc
SRCS = $(wildcard $(SRCDIR)/*.cc)
#SRCS := $(filter-out $(EXEC_SRC),$(SRCS))
EXEC = main
DEP = $(patsubst $(SRCDIR)/%.cc,$(BUILDDIR)/%.o,$(SRCS))

all: dir $(DEP) $(EXEC)

dir:
	mkdir $(BUILDDIR)
clean:
	rm -rf $(BUILDDIR) $(EXEC) atom.bond.data

$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
	$(CXX) $(CFLAGS) -c $^ -o $@

$(EXEC): $(DEP) $(EXEC_SRC)
	$(CXX) $(CFLAGS) $(DEP) -o $@
