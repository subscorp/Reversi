
#include "ReversiServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;
#define MAX_CONNECTED_CLIENTS 10

ReversiServer::ReversiServer(int port): port(port), serverSocket(0)
{
	cout << "starting server..." << endl;
}

void ReversiServer::start()
{
	int connectedPlayers = 0;
	int turn = 1;
	int shouldStop = 0;
	int n;
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

		connectedPlayers++;
		if(connectedPlayers == 1)
		{
			cout << "player 1 connected to server" << endl << "waiting for other player to join..." << endl;
		}

		int clientSocket2 = accept(serverSocket, (struct sockaddr *)&clientAddress,
				&clientAddressLen);

		connectedPlayers++;
		if(connectedPlayers == 2)
		{
			cout << "player 2 connected to server" << endl;

			// send turn for two players
			n = write(clientSocket,&turn, sizeof(turn));
			if(n == -1)
			{
				throw "Error writing turn to socket1";
			}
			turn = 2;

			n = write(clientSocket2, &turn, sizeof(turn));
			if(n == -1)
			{
				throw "Error writing turn to socket2";
			}
		}
		//cout << "Client connected" << endl;
		if(clientSocket == -1)
			throw "Error on accept";

		while(true)
		{
			/*
			here we are getting move from one client socket and writing to the other
			we also check here if the game is over:
			the return value from handleClient indicates if no moves are available for both players
			and the following read command checks if the board is full
			 */

			shouldStop = handleClient(clientSocket, clientSocket2);
			if(shouldStop)
				break;

			shouldStop = handleClient(clientSocket2, clientSocket);
			if(shouldStop)
				break;
		}

		// Close communication with the client
		close(clientSocket);
		close(clientSocket2);

		//reset helper variables
		connectedPlayers = 0;
		turn = 1;
		shouldStop = 0;
	}
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
