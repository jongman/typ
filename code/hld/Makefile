OPT=-O3
all: hld simple lib
clean: 
	rm -f hld simple lib

hld: hld.cpp
	g++ --std=c++11 $(OPT) hld.cpp -o hld

simple: simple.cpp
	g++ --std=c++11 $(OPT) simple.cpp -o simple

lib: lib.cpp
	g++ --std=c++11 $(OPT) lib.cpp -o lib


