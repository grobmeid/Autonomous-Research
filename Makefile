cc = gcc -g
CC = g++ -g

CCFLAGS = -Wall -O4 -ansi -pedantic
SRCS = src/*
BIN = bin/Test
LIBS = lib/*
ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
		BIN := $(BIN).exe
else
		BIN := $(BIN).out
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX -lpthread
    endif
    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D OSX -lpthread
    endif
endif

all:
	[ -d "bin" ] && echo "Directory bin Exists" || mkdir bin
	[ -d "lib" ] && echo "Directory lib Exists" || mkdir lib
	$(CC) -c $(CCFLAGS) $(SRCS)
	mv *.o lib
	$(CC) $(CCFLAGS) $(LIBS) -o $(BIN)

clean:
	[ -d "bin" ] && echo "Cleaning bin"; rm bin/*;

run:
	./$(BIN)
