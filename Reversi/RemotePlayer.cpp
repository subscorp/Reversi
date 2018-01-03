
#include <iostream>
using namespace std;
#include "RemotePlayer.h"
#define BUFFER_SIZE 1024

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

int* RemotePlayer::makeMove(Board *board, int* move)
{
	string input;

	//the current player is this player
	if(local)
	{
		//if the player can do move, get it and send to the server
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

			input = "play " + input;
			char buffer[BUFFER_SIZE] = {0};
			strcpy(buffer, input.c_str());
			if(write(clientSocket, buffer, BUFFER_SIZE) == -1)
			{
				throw "Error writing move";
			}
		}

		//if the player can't do move, indicate it by move = 0,0 and send to the server
		else
		{
			cout << "no moves available for " << color << endl << endl;
			move[0] = 0;
			move[1] = 0;
			char buffer[BUFFER_SIZE] = {"play 0 0"};
			if(write(clientSocket, buffer, BUFFER_SIZE) == -1)
			{
				throw "Error writing move";
			}
		}

	} // if local

	// if the current player is the other player get his move from the server
	else
	{
		char buffer[BUFFER_SIZE] = {0};
		cout << "waiting for other player's move..." << endl;
		if(read(clientSocket, buffer, BUFFER_SIZE) == -1)
		{
			throw "Error reading move";
		}

		string result(buffer);
		if (result == "") {
			cout << "Disconnected from the server" << endl;
			close(clientSocket);
			exit(1);
		}

		vector<string> parts = split(result, " ");

		move[0] = (int)parts[0][0] - 48;
		move[1] = (int)parts[1][0] - 48;

		if(move[0] == 0 && move[1] == 0)
			cout << "no moves available for " << color << endl;

		else
			cout << color << " played (" << move[0] << "," << move[1] << ")"
					<< endl;

	}
	return move;
}

