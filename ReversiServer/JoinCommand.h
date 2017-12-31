/*
 * JoinCommand.h
 *
 *  Created on: Dec 29, 2017
 *      Author: ori
 */

#ifndef JOINCOMMAND_H_
#define JOINCOMMAND_H_

#include "Command.h"
#include "ReversiServer.h"
#include <iostream>

class JoinCommand: public Command
{
public:
	ReversiServer *server;

	JoinCommand(ReversiServer *server) {
		this->server = server;
	}
	~JoinCommand();

	virtual string execute(vector<string> args, int clientSocket)
	{
		cout << "in join command" << endl;
		if (args.size() < 2)
			return "";

		string name = args[1];

		if (this->server->games.count(name) == 0) {
			cout << "Game "<<name<< "does not exist!" <<endl;
			return "";
		}

		GameInfo game = this->server->games[name];
		game.client2 = clientSocket;
		this->server->games[name] = game;
		return "";
	}
};

#endif /* JOINCOMMAND_H_ */
