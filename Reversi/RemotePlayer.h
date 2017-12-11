/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#pragma once
#include "Board.h"
#include "StandardLogic.h"
#include "Player.h"
#include <stdlib.h>
#include<string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

using namespace std;

class RemotePlayer: public Player
{
public:
	//default constructor and destructor for LocalPlayer
	RemotePlayer();
	~RemotePlayer();

	//constructor for Remote Player that takes color and logic as parameters
	RemotePlayer(int socket, Logic *logic, int local);


	void decideTurn();

	//let the player make a move
	int* makeMove(Board *board, int* move);

private:
	const char *serverIP;
	int serverPort;
	int clientSocket;
	int local;
};
