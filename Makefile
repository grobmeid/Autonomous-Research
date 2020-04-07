cc = gcc -g
CC = g++ -g

CCFLAGS = -Wall -O3 -ansi -pedantic
LLFLAGS = -Wall -O3
SRCS = src/*.cpp
BIN = bin/Test
LIBS = lib/*
ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
		BIN := $(BIN).exe
else
		BIN := $(BIN).out
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX
				LLFLAGS = -lpthread
    endif
    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D OSX
				LLFLAGS = -lpthread
    endif
endif

all:
	[ -d "bin" ] && echo "Directory bin Exists" || mkdir bin
	[ -d "lib" ] && echo "Directory lib Exists" || mkdir lib
	$(CC) -c $(CCFLAGS) $(SRCS)
	mv *.o lib
	$(CC) $(LLFLAGS) $(LIBS) -o $(BIN)

clean:
	[ -d "bin" ] && echo "Cleaning bin"; rm bin/*;

run:
	./$(BIN)
