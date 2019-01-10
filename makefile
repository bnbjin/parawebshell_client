CALL_FROM_DIR=$(shell pwd)
ABS_PWPATH=$(abspath $(lastword $(MAKEFILE_LIST)))
ABS_PWDIR=$(shell dirname $(ABS_PWPATH))
ROOT=$(ABS_PWDIR)
BIN=$(ROOT)/bin
LIB=$(ROOT)/lib
PROJECT=parawebshell
COMPILE_OPT=-std=c++11 -g
LINK_OPT=


$(BIN)/$(PROJECT) : $(ROOT)/main.cpp
	g++ $(COMPILE_OPT) -c $(ROOT)/main.cpp -o $(BIN)/main.o
	g++ $(BIN)/main.o $(LINK_OPT) -o $(BIN)/$(PROJECT)

clean :
	rm -f $(BIN)/*.o
	rm -f $(BIN)/$(PROJECT)
