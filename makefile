BIN=bin
INC=inc
SRC=src
PROJECT=parawebshell
COMPILE_OPT=-std=c++11

$(PROJECT) : main.cpp
	g++ $(COMPILE_OPT) -c main.cpp
	g++ main.o -o $(PROJECT)

clean :
	rm -rf *.o
	rm $(PROJECT)
