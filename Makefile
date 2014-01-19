CC=clang

CFLAGS=-c -Weverything

EXE=putrefy

BIN=./bin
SRC=./src
OBJ=./obj
INC=./inc

all: $(BIN)/$(EXE)

run: all
	$(BIN)/$(EXE) $(ARGS)

$(BIN)/$(EXE): $(OBJ)/main.o
	$(CC) $(OBJ)/main.o -o $(BIN)/$(EXE)

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) $(SRC)/main.c -I$(INC) -o $(OBJ)/main.o

clean:
	rm -rvf $(OBJ)/*.o $(BIN)/$(EXE)
