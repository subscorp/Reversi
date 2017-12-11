/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include <iostream>
using namespace std;
#include "RemotePlayer.h"

RemotePlayer::RemotePlayer()
{
}
RemotePlayer::RemotePlayer(int socket, Logic *logic, int local) :
		clientSocket(socket), local(local) {
	this->logic = logic;
}

RemotePlayer::~RemotePlayer()
{
}

void RemotePlayer::decideTurn() {

	int turn;
	int n;

	n = read(clientSocket,&turn,sizeof(turn));
	if(n == -1) {
		throw "Error reading turn from socket";
	}
	if(turn == 1)
	{
		color = 'X';
	}
	else
		color = 'O';
	cout << "you are player " << color << endl;
}

int* RemotePlayer::makeMove(Board *board, int* move)
{
	string input;
	int n;

	if(local)
	{
		if (canDoMove(board))
		{
			cout << color << ": it's your move." << endl;
			do {
				cout << "your possible moves: ";
				logic->printPossibleMoves(color, board);
				cout << "please insert move in the form \"row col\" and press enter" << endl;
				cout << endl;
				std::getline(std::cin, input);
			} while (!logic->moveIsValid(color, input, board));
			move[0] = (int)input[0] - 48;
			move[1] = (int)input[2] - 48;
			n = write(clientSocket, &move[0], sizeof(move[0]));
			if(n == -1) {
				throw "Error writing move[0]";
			}
			n = write(clientSocket, &move[1], sizeof(move[1]));
			if(n == -1) {
				throw "Error writing move[1]";
			}

		}
		else
		{
			cout << "no moves available for " << color << endl << endl;
			move[0] = 0;
			move[1] = 0;
			n = write(clientSocket, &move[0], sizeof(move[0]));
			if(n == -1) {
				throw "Error writing move[0]";
			}
			n = write(clientSocket, &move[1], sizeof(move[1]));
			if(n == -1) {
				throw "Error writing move[1]";
			}
		}

	} // if local
	else
	{
		cout << "waiting for other player's move..." << endl;
		n = read(clientSocket, &move[0], sizeof(move[0]));
		if(n == -1) {
			throw "Error reading move[0]";
		}

		n = read(clientSocket, &move[1], sizeof(move[1]));
		if(n == -1) {
			throw "Error reading move[1]";
		}
		if(move[0] == 0 && move[1] == 0)
			cout << "no moves available for " << color << endl << endl;
		else
			cout << color << " played (" << move[0] << "," << move[1] << ")"
					<< endl;
	}
	//only for debuging
	return move;
}

