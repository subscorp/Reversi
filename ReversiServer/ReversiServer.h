
#pragma once
#define BUFFER_SIZE 1024

#include <vector>
#include <string>
#include <map>
#include <pthread.h>
#include "ThreadPool.h"
#include <thread>
#include "Command.h"

using namespace std;


struct GameInfo
{
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
	string executeCommand(string command, vector<string> args, int socket);
	map<string, GameInfo> games;
	vector<pthread_t> threads;
	int serverSocket; // the socket's file descriptor
	vector<int> clientSockets;

private:
	int port;
	map<string, Command *> commandsMap;
	pthread_t serverThreadId;
};

