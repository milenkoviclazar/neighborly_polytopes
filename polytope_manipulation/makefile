CXX=mpic++
CXXFLAGS=-O3 -DUSE_MPI -std=c++0x -Wall -pedantic

check : main.o io_utils.o search.o
	$(CXX) $(CXXFLAGS) -o check main.o io_utils.o search.o

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
io_utils.o : io_utils.cpp io_utils.h
	$(CXX) $(CXXFLAGS) -c io_utils.cpp
search.o : search.cpp search.h
	$(CXX) $(CXXFLAGS) -c search.cpp

clean :
	rm check main.o io_utils.o search.o
