/*
 * CloseCommand.h
 *
 *  Created on: Dec 29, 2017
 *      Author: ori
 */

#ifndef CLOSECOMMAND_H_
#define CLOSECOMMAND_H_

#include "Command.h"
#include "ReversiServer.h"
#include <iostream>

class CloseCommand: public Command
{
public:
	ReversiServer *server;
	CloseCommand(ReversiServer* server) {
		this->server = server;
	}
	~CloseCommand();

	virtual string execute(vector<string> args, int clientSocket)
	{
		cout << "in close command" << endl;
		return "";

	}
};

#endif /* CLOSECOMMAND_H_ */
