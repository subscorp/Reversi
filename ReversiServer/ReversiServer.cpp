
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include "ReversiServer.h"
#include "StartCommand.h"
#include "ListGamesCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "CloseCommand.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 10

struct ThreadArgs
{
	int socket;
	pthread_t tid;
	ReversiServer *self;
};

ReversiServer::ReversiServer(int port): port(port), serverSocket(0),  serverThreadId(0)
{
	cout << "starting server..." << endl;
	commandsMap["start"] = new StartCommand(this);
	commandsMap["list_games"] = new ListGamesCommand(this);
	commandsMap["join"] = new JoinCommand(this);
	commandsMap["play"] = new PlayCommand(this);
	commandsMap["close"] = new CloseCommand(this);
}

ReversiServer::~ReversiServer()
{
	map<string, Command *>::iterator it;
	for (it = commandsMap.begin(); it != commandsMap.end(); it++)
	{
		delete it->second;
	}
}

string ReversiServer::executeCommand(string command, vector<string> args, int socket)
{
	if (commandsMap.count(command) > 0)
	{
		Command *commandObj = commandsMap[command];
		return commandObj->execute(args, socket);
	}
	return "Command not exist";
}

static vector<string> split(const string &str, string delimeter)
{
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

/*
void* loopThread(void* arg)
{
	ThreadArgs args;
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
		args.tid = tid;
		pthread_create(&tid, NULL, handleClientThread, &args);
		this->threads.push_back(tid);
		cout << "Thread created" << endl;
	} // while
	close(serverSocket);
}
*/

void* handleClientThread(void *arg)
{
	//ThreadArgs assignments
	ThreadArgs *args = (ThreadArgs *) arg;
	int clientSocket = args->socket;
	pthread_t tid = args-> tid;
	ReversiServer *self = args->self;


	while (true)
	{
		char buffer[BUFFER_SIZE] = {0};

		// reading message from client
		if(read(clientSocket, buffer, BUFFER_SIZE) == 0)
		{
			cout << "closing socket " << clientSocket << endl;

			// move on to close the game
			break;
		}

		//parsing the message
		string message(buffer);
		vector<string> parts = split(message, " "); // start mygame

		//executing the command we got from the message
		string result = self->executeCommand(parts[0], parts, clientSocket);
		if (result != "")
		{
			//responding to the client
			char buffer[BUFFER_SIZE] = {0};
			strcpy(buffer, result.c_str());
			if(write(clientSocket, buffer, BUFFER_SIZE) == -1)
			{
				cout << "Error writing response" << endl;
			}
		}

	} //while

	//closing the game

	//erasing current thread
	int i = 0;
	vector<pthread_t>::iterator it;
	for(it = self->threads.begin(); it < self->threads.end(); it++)
	{
		if(*it == tid)
		{
			self->threads.erase(it);
			break;
		}
		i++;
	}

	//erasing the game from the games list
	map<string, GameInfo>::iterator it2;
	int j = 0;
	for (it2 = self->games.begin(); it2 != self->games.end(); it2++)
	{
		if(it2->second.client1 == clientSocket || it2->second.client2 == clientSocket)
		{
			self->games.erase(it2);
			break;
		}
		j++;
	}

	//closing the client socket
	close(clientSocket);

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
		args.tid = tid;
		pthread_create(&tid, NULL, handleClientThread, &args);
		this->threads.push_back(tid);
		cout << "Thread created" << endl;
	} // while
	close(serverSocket);
}

void ReversiServer::stop()
{
	pthread_cancel(serverThreadId);
	close(serverSocket);
	cout << "Server stopped" << endl;
}



