BIN=bin
INC=inc
SRC=src
PROJECT=parawebshell
COMPILE_OPT=-std=c++11

$(PROJECT) : main.cpp
	g++ $(COMPILE_OPT) -c main.cpp -o $(BIN)/main.o
	g++ main.o -o $(BIN)/$(PROJECT)

clean :
	rm -rf $(BIN)/*.o
	rm -f $(BIN)/$(PROJECT)
