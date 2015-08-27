Eigen_dir=/usr/local/include/eigen3/
CC_OBJECT_FLAGS= -c -Wall -std=c++11 -I $(Eigen_dir)
$(VERBOSE).SILENT:

all: clean plsa main exe

plsa:
	 g++ plsa.cpp $(CC_OBJECT_FLAGS)
main:
	g++ main.cpp $(CC_OBJECT_FLAGS)

exe:
	g++ main.o plsa.o -o m

clean:
	rm -f main.o plsa.o m
