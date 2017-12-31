/*
 * PlayCommand.h
 *
 *  Created on: Dec 29, 2017
 *      Author: ori
 */

#ifndef PLAYCOMMAND_H_
#define PLAYCOMMAND_H_

#include "Command.h"
#include "ReversiServer.h"
#include <iostream>

class PlayCommand : public Command
{
public:
	ReversiServer *server;
	PlayCommand(ReversiServer *server) {
		this->server = server;
	}
	~PlayCommand();

	virtual string execute(vector<string> args, int clientSocket)
	{
		cout << "in play command" << endl;
		return "";
	}
};

#endif /* PLAYCOMMAND_H_ */
