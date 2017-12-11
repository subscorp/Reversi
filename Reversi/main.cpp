/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include <iostream>
#include "Board.h"
#include "LocalPlayer.h"
#include "AIPlayer.h"
#include "RemotePlayer.h"
#include "GameManager.h"

using namespace std;

int connectToServer(char *, int);

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

		int socket = connectToServer("127.0.0.1", 8882);
		thisPlayer = new RemotePlayer(socket, gameLogic, 1);
		try {
			thisPlayer->decideTurn();
		} catch (const char *msg) {
			cout << "Failed to connect to server. Reason: " << msg << endl;
			exit(-1);
		}
		otherPlayer = new RemotePlayer(socket, gameLogic, 0);
		otherPlayer->setColor(thisPlayer->getColor() == 'X' ? 'O' : 'X');
		cout << "starting game against remote player" <<endl << endl;
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

int connectToServer(char *serverIP, int serverPort)
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
	cout << "waiting for other player to join..." << endl;
	return clientSocket;
}

