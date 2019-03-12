CALL_FROM_DIR=$(shell pwd)
ABS_PWPATH=$(abspath $(lastword $(MAKEFILE_LIST)))
ABS_PWDIR=$(shell dirname $(ABS_PWPATH))
ROOT=$(ABS_PWDIR)
BIN=$(ROOT)/bin
LIB=$(ROOT)/lib
TESTDIR=$(ROOT)/test
PROJECT=parawebshell
INC_DIR=./
COMPILE_OPT=-I$(INC_DIR) -I/usr/include/ -std=c++11 -g
LINK_OPT=-L/usr/lib/boost -lboost_stacktrace_basic -lboost_system -ldl -lpthread
TEST_LINK_OPT=-L/usr/lib/boost -lboost_test
UNIT_TEST_CASE_OBJ= http_test.o

.PHONY: release test http_test clean

release : $(BIN)/ps.o $(BIN)/http.o $(BIN)/main.o
	g++ $(BIN)/*.o $(LINK_OPT) -o $(BIN)/$(PROJECT)

$(BIN)/ps.o : ps.hpp ps.cpp
	g++ $(COMPILE_OPT) -c $(ROOT)/ps.cpp -o $@

$(BIN)/http.o : http.hpp http.cpp pwsque.hpp
	g++ $(COMPILE_OPT) -c $(ROOT)/http.cpp -o $(BIN)/http.o

$(BIN)/main.o : $(ROOT)/main.cpp
	g++ $(COMPILE_OPT) -c $(ROOT)/main.cpp -o $(BIN)/main.o 

test : http_test 

http_test :
	g++ $(COMPILE_OPT) -c $(ROOT)/$@.cpp -o $(TESTDIR)/$@.o
	g++ $(TESTDIR)/$@.o $(LINK_OPT) $(TEST_LINK_OPT) -o $(TESTDIR)/$@

clean :
	rm -f $(BIN)/*
	rm -f $(TESTDIR)/*
