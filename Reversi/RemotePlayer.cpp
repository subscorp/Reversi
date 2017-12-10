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
RemotePlayer::RemotePlayer(const char *serverIP, int serverPort, Logic *logic, int local):
serverIP(serverIP), serverPort(serverPort),
		clientSocket(0), local(local) {
	this->logic = logic;
	cout << "Client" << endl;
}
RemotePlayer::RemotePlayer(Logic *logic, int local)
{
	this->logic = logic;
	this->local = local;
}

RemotePlayer::~RemotePlayer()
{
}

void RemotePlayer::connectToServer() {

	int turn;
	int n;
	// Create a socket point
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket == -1) {
		throw "Error opening socket";
	}
	// Convert the ip string to a network address
	struct in_addr address;
	if(!inet_aton(serverIP, &address)) {
		throw "Can't parse IP address";
	}
	// Get a hostent structure for the given host address
	struct hostent *server;
	server = gethostbyaddr((const void *)&address, sizeof(address), AF_INET);
	if(server == NULL) {
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
	if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
		throw "Error connecting to server";
	}
	n = read(clientSocket,&turn,sizeof(turn));
	if(n == -1) {
		throw "Error reading turn from socket";
	}
	cout << "Connected to server" << endl;
	cout << "turn:" << turn << endl;
	if(turn == 1)
	{
		color = 'X';
		cout << "waiting for other player to join..." << endl;
	}
	else
		color = 'O';
	cout << "you are player " << color << endl;
}

int RemotePlayer::sendExercise(int arg1, char op, int arg2) {
	int turn;
	if(color == 'X')
		turn = 1;
	else
		turn = 2;
	// Write the exercise arguments to the socket
	int n = write(clientSocket, &arg1, sizeof(arg1));
	if(n == -1) {
		throw "Error writing arg1 to socket";
	}
	n = write(clientSocket, &op, sizeof(op));
	if(n == -1) {
		throw "Error writing op to socket";
	}
	n = write(clientSocket, &arg2, sizeof(arg2));
	if(n == -1) {
		throw "Error writing arg2 to socket";
	}

	n = write(clientSocket,&turn,sizeof(turn));
	// Read the result from the server
	int result;
	n = read(clientSocket, &result, sizeof(result));
	if(n == -1) {
		throw "Error reading result from socket";
	}
	return result;
}

int* RemotePlayer::makeMove(Board *board, int* move)
{
	/*
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
		//only for debuging
		return move;
	}
	else
	{
		n = read(clientSocket, &move[0], sizeof(move[0]));
		if(n == -1) {
			throw "Error reading move[0]";
		}
		n = read(clientSocket, &move[1], sizeof(move[1]));
		if(n == -1) {
			throw "Error reading move[1]";
		}
		return move;
	}
	*/


		int num1, num2;
		char op;
		while(true) {
			cout << "Enter an exercise (e.g., 15*19): ";
			cin >> num1 >> op >> num2;
			cout << "Sending exercise: " << num1 << op << num2 << endl;

			try {
				int result = sendExercise(num1, op, num2);
				cout << "Result: " << result << endl;
			} catch (const char *msg) {
				cout << "Failed to send exercise to server. Reason: " << msg << endl;
			}
		}

}

