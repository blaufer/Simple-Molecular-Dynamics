# Use make with where='-Dhome' or where='-Dcori' to get
# the correct potential directory

SHELL = /bin/sh
EXE = md

#----- Compilers --------------------------------
CXX = mpicxx
CC = mpicc


#----- Compiler flags ---------------------------
CFLAGS = -O2 #-g
CXXFLAGS = -O2 -std=c++17 #-g -std=c++17


#----- Stops files from -------------------------
#----- calling these by accident ----------------
.PHONY : clean clean-exe clean-all


#----- Subdirectories ---------------------------
SRCDIR = ./src
OBJDIR = ./obj

#----- List of created .o files -----------------
ofiles = $(addprefix $(OBJDIR)/, \
	vectors.o \
	lattice.o \
	lj.o \
	verlet.o \
	dump.o \
	log.o \
	temp_press.o \
	velocity.o \
	md.o)

#----- Compilation rules ------------------------
$(EXE) : $(ofiles)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/md.o : $(SRCDIR)/md.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


#----- Clean up ---------------------------------
clean :
	$(RM) $(OBJDIR)/*.o

clean-exe :
	$(RM) $(EXE)

clean-all : clean clean-exe
