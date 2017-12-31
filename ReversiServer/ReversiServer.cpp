
#include "ReversiServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

#include "StartCommand.h"
#include "ListGamesCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "CloseCommand.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 10

struct ThreadArgs {
	int socket;
	ReversiServer *self;
};

ReversiServer::ReversiServer(int port): port(port), serverSocket(0)
{
	cout << "starting server..." << endl;
	commandsMap["start"] = new StartCommand(this);
	commandsMap["list_games"] = new ListGamesCommand(this);
	commandsMap["join"] = new JoinCommand(this);
	commandsMap["play"] = new PlayCommand(this);
	commandsMap["close"] = new CloseCommand(this);
}

ReversiServer::~ReversiServer() {
	map<string, Command *>::iterator it;
	for (it = commandsMap.begin(); it != commandsMap.end(); it++)
	{
		delete it->second;
	}
}

string ReversiServer::executeCommand(string command, vector<string> args, int socket)
{
	if (commandsMap.count(command) > 0) {
		cout << "Running command "<<command<<endl;
		Command *commandObj = commandsMap[command];
		return commandObj->execute(args, socket);
	}
	return "Command not exist";
}

static vector<string> split(const string &str, string delimeter) {
	vector<string> result;
	int prevPos = 0, position = 0;
	string part;
	do {
		position = str.find(delimeter, prevPos);
		if (position == string::npos)
			position = str.length(); // last part, extract until end
		part = str.substr(prevPos, position - prevPos);
		result.push_back(part);
		prevPos = position + delimeter.length();
	} while (position < (int) str.length() && prevPos < (int) str.length());
	return result;
}

void* handleClientThread(void *arg) {
	//temporal variable for current assignment
	ThreadArgs *args = (ThreadArgs *) arg;
	int clientSocket = args->socket;
	ReversiServer *self = args->self;
	int shouldStop = 1;

	while (true) {
		char buffer[BUFFER_SIZE] = {0};

		// reading message from client
		if(read(clientSocket, buffer, BUFFER_SIZE) == -1)
		{
			cout << "Error reading from client" << endl;
			//exit(1);
		}

		string message(buffer);
		vector<string> parts = split(message, " "); // start mygame
		cout << "Got message " << message << " parts: "<< parts.size() << endl;
		if (parts.size() > 0) {
			string result = self->executeCommand(parts[0], parts, clientSocket);
			char buffer[BUFFER_SIZE] = {0};
			strcpy(buffer, result.c_str());
			cout << "Sending message: " << result << endl;
			if(write(clientSocket, buffer, BUFFER_SIZE) == -1)
			{
				cout << "Error writing response" << endl;
			}

		} // if

	} // while
	return NULL;
}


void ReversiServer::start()
{
	ThreadArgs args;

	//create a socket point
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSocket == -1)
	{
		throw "Error opening socket";
	}

	//Assign a local address to the socket
	struct sockaddr_in serverAddress;
	bzero((void *)&serverAddress,
			sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);
	if(bind(serverSocket, (struct sockaddr *)&serverAddress,
			sizeof(serverAddress)) == -1)
	{
		throw "Error on binding";
	}

	// Start listening to incoming connections
	listen(serverSocket, MAX_CONNECTED_CLIENTS);

	// Define the client socket's structures
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen;

	while(true)
	{
		cout << "Waiting for client connections..." << endl;

		//Accept a new client connection
		int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress,
				&clientAddressLen);

		cout << "Client connected" << endl;
		if(clientSocket == -1)
			throw "Error on accept";

		pthread_t tid;
		args.socket = clientSocket;
		args.self = this;
		pthread_create(&tid, NULL, handleClientThread, &args);
		this->threads.push_back(tid);
		cout << "Thread created" << endl;
	} // while
	close(serverSocket);
}

// Handle requests from a specific client
int ReversiServer::handleClient(int clientSocket, int clientSocket2)
{
	//temporal variable for current assignment
	int boardSize = 64;

	int arg1, arg2, numPawns;
	int shouldStop = 1;
	static int numCantMove = 0;

		//reading move and number of pawns from clientSocket
		int n = read(clientSocket, &arg1, sizeof(arg1));
		if(n == -1)
		{
			cout << "Error reading arg1" << endl;
			return 1;
		}
		if(n == 0)
		{
			cout << "Client disconnected" << endl;
			return 1;
		}

		n = read(clientSocket, &arg2, sizeof(arg2));
		if(n == -1)
		{
			cout << "Error reading arg2" << endl;
			return 1;
		}

		n = read(clientSocket, &numPawns, sizeof(numPawns));
		if(n == -1)
		{
			cout << "Error reading numPawns" << endl;
			return 1;
		}

		cout << "Got move " << arg1 <<"," << arg2 << endl;

		//writing move to the other client socket
		n = write(clientSocket2, &arg1, sizeof(arg1));
		if(n == -1)
		{
			cout << "Error writing arg1" << endl;
			return 1;
		}
		n = write(clientSocket2, &arg2, sizeof(arg2));
		if(n == -1)
		{
			cout << "Error writing arg2" << endl;
			return 1;
		}

		// checks if the board is full
		if(numPawns == boardSize)
			return shouldStop;

		//checks if both players has no moves available
		if(arg1 == 0 && arg2 == 0)
		{
			numCantMove++;
			if(numCantMove == 2)
				return shouldStop;
			if(numCantMove > 2)
				numCantMove = 0;
		}
		else
			numCantMove = 0;


		cout << "written move to other player" << endl;
		return !shouldStop;
}

void ReversiServer::stop()
{
	close(serverSocket);
}



