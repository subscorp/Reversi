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

RemotePlayer::RemotePlayer(char color, Logic *logic, Client *client)
{
	this->color = color;
	this->logic = logic;
	this->client = client;
}

RemotePlayer::~RemotePlayer()
{
}

int* RemotePlayer::makeMove(Board *board, int* move)
{
		int num1, num2;
		char op;
		while(true) {
			cout << "Enter an exercise (e.g., 15*19): ";
			cin >> num1 >> op >> num2;
			cout << "Sending exercise: " << num1 << op << num2 << endl;

			try {
				int result = client->sendExercise(num1, op, num2);
				cout << "Result: " << result << endl;
			} catch (const char *msg) {
				cout << "Failed to send exercise to server. Reason: " << msg << endl;
			}
		}
}

