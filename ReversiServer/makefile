all: server

# Put here all the common files
COMMON_SOURCES = ReversiServer.cpp CloseCommand.cpp Command.cpp CommandsManager.cpp JoinCommand.cpp ListGamesCommand.cpp PlayCommand.cpp StartCommand.cpp PrintCommand.cpp

server:
	g++ -std=c++0x -pthread main.cpp $(COMMON_SOURCES) -I. -o a.out
