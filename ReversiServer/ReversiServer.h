
#pragma once
#define BUFFER_SIZE 1024

#include <vector> //new
#include <string> // new
#include <map> // new
#include <pthread.h>
#include <thread>
#include "Command.h"

using namespace std;

struct GameInfo {
	int client1;
	int client2;
};

class ReversiServer
{

public:
	friend class Command;
	ReversiServer(int port);
	~ReversiServer();
	void start();
	void stop();
	void *loopThread(void *arg);
	string executeCommand(string command, vector<string> args, int socket);
	//map<string, int > games;
	//CommandsManager commandsManager;
	map<string, GameInfo> games;
	vector<pthread_t> threads;

private:
	int port;
	int serverSocket; // the socket's file descriptor

	int handleClient(int clientSocket, int clientSocket2);
	map<string, Command *> commandsMap;
};

