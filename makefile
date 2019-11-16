#
# Specifiy the target
all:	program4

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable

program4:	dynamic.o
	g++	dynamic.o	-o program4

# Specify how the object files should be created from source files

dynamic.o:	dynamic.cpp
	g++ -g -Wall -std=c++11 -c dynamic.cpp


# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o program4
