# name: ori hirshfeld
# id: 201085776

all: server

# Put here all the common files
COMMON_SOURCES = ReversiServer.cpp Command.cpp JoinCommand.cpp ListGamesCommand.cpp PlayCommand.cpp StartCommand.cpp

server:
	g++ -std=c++0x -pthread main.cpp $(COMMON_SOURCES) -I. -o a.out
