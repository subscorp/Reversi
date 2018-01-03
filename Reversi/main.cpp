/******************************************
*Ori Hirshfeld
*201085776
******************************************/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Board.h"
#include "LocalPlayer.h"
#include "AIPlayer.h"
#include "RemotePlayer.h"
#include "GameManager.h"
#define BUFFER_SIZE 1024

using namespace std;

int connectToServer(const char *, int);
char menuLoop(int socket);

int main()
{
	int choice;
	GameManager *manager;
	Logic *gameLogic;
	Player *playerO;
	Player *playerX;
	RemotePlayer *thisPlayer;
	RemotePlayer *otherPlayer;

	//presenting choices to the user and getting input
	cout <<"Welcome to Reversi!" << endl;
	cout << "enter 1 to play against AI player" << endl;
	cout << "enter 2 to play against Human player" <<endl;
	cout << "enter 3 to play against remote player" << endl;
	cin >> choice;
	cin.ignore();
	switch(choice)
	{

	//using standard logic and playing against AI player
	case 1:
	{
		gameLogic = new StandardLogic();
		playerX = new LocalPlayer('X', gameLogic);
		playerO = new AIPlayer('O', gameLogic);
		cout << "starting a game against AI player" <<endl << endl;
		manager = new GameManager(gameLogic, playerX, playerO);
		break;
	}

	//using standard logic and playing against another human player
	case 2:
	{
		cout << "starting game against Human player" <<endl << endl;
		manager = new GameManager();
		break;
	}

	//using standard logic and playing against remote player
	case 3:
	{
		gameLogic = new StandardLogic();

		//reading from file IP and port number
		int portNumber;
		string IP;
		string portAsString;
		ifstream myfile("clientConnectionDetails.txt");
		if (myfile.is_open())
		{
			getline(myfile,IP);
			getline(myfile,portAsString);
			myfile.close();
		}
		else
			cout << "Unable to open file";

		portNumber = atoi(portAsString.c_str());
		int socket = connectToServer(IP.c_str(), portNumber);
		int color = menuLoop(socket);

		thisPlayer = new RemotePlayer(socket, gameLogic, 1);
		thisPlayer->setColor(color);
		otherPlayer = new RemotePlayer(socket, gameLogic, 0);
		otherPlayer->setColor(thisPlayer->getColor() == 'X' ? 'O' : 'X');

		cout << "starting game against remote player" << endl << endl;
		manager = new GameManager(gameLogic, thisPlayer, otherPlayer);
		break;
	}
	//defualt case is the same as case 2
	default:
	{
		GameManager manager3;
		manager3.runGame();
		break;
	}

	}
	manager->runGame();
	delete manager;

	return 0;
}

//menu loop for case 3
char menuLoop(int clientSocket)
{
	while (true)
	{
		cout << "enter start name to start a new game named \"name\"" << endl;
		cout << "enter join name to join the game named \"name\"" << endl;
		cout << "enter list_games to see a list of available games" << endl;

		char buffer[BUFFER_SIZE] = {0};
		string input;
		std::getline(std::cin, input);

		strcpy(buffer, input.c_str());
		if(write(clientSocket, buffer, BUFFER_SIZE) == -1)
		{
			throw "Error writing to server";
		}

		if(read(clientSocket, buffer, BUFFER_SIZE) == -1)
		{
			cout << "Message: " << buffer << endl;
			throw "Error reading from server";
		}
		string result(buffer);
		if (result == "start_x")
			return 'X';
		else if (result == "start_o")
			return 'O';

		cout << result << endl;
	} // while
	return '-';
}

//connecting the client to the server
int connectToServer(const char *serverIP, int serverPort)
{
	int clientSocket;
	// Create a socket point
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket == -1)
	{
		throw "Error opening socket";
	}
	// Convert the ip string to a network address
	struct in_addr address;
	if(!inet_aton(serverIP, &address))
	{
		throw "Can't parse IP address";
	}
	// Get a hostent structure for the given host address
	struct hostent *server;
	server = gethostbyaddr((const void *)&address, sizeof(address), AF_INET);
	if(server == NULL)
	{
		throw "Host is unreachable";
	}

	// Create a structure for the server address
	struct sockaddr_in serverAddress;
	bzero((char *)&address, sizeof(address));

	serverAddress.sin_family = AF_INET;
	memcpy((char *)&serverAddress.sin_addr.s_addr, (char
			*)server->h_addr, server->h_length);
	// htons converts values between host and network byte orders
	serverAddress.sin_port = htons(serverPort);

	// Establish a connection with the TCP serer
	if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
	{
		throw "Error connecting to server";
	}
	cout << "Connected to server" << endl;

	return clientSocket;
}

