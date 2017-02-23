CXX=mpic++
CXXFLAGS=-O3 -DUSE_MPI -std=c++0x -Wall -pedantic

check : main.o io_utils.o baralic.o
	$(CXX) $(CXXFLAGS) -o check main.o io_utils.o baralic.o

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
io_utils.o : io_utils.cpp io_utils.h
	$(CXX) $(CXXFLAGS) -c io_utils.cpp
baralic.o : baralic.cpp baralic.h
	$(CXX) $(CXXFLAGS) -c baralic.cpp

clean :
	rm check main.o io_utils.o baralic.o
