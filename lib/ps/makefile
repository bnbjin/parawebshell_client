CURDIR= $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))

COMPILE_OPT=-I./inc

ps : $(BIN)/ps.o

$(BIN)/ps.o : $(CURDIR)/inc/pws/ps/ps.hpp $(CURDIR)/ps.cpp
	g++ $(COMM_COMPILE_OPT) $(COMPILE_OPT) -c $(CURDIR)/ps.cpp -o $(BIN)/ps.o
