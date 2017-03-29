CC= g++ -std=c++11
CFLAGS= -pthread -lncurses -lpanel
SRC_FILES= $(wildcard ./src/*.cpp)

all:
	$(CC) $(SRC_FILES) -I ./include/ $(CFLAGS) -o ./bin/superchat.exe

