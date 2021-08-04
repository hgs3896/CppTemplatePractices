CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb -D_DEBUG

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lpthread
EXECUTABLE	:= main

.PHONY: all run make_dirs clean

all: $(BIN) $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN):
	mkdir -p $(BIN)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(make_dirs)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	rm -rf $(BIN)/*
