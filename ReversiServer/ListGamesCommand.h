/*
 * ListGamesCommand.h
 *
 *  Created on: Dec 29, 2017
 *      Author: ori
 */

#ifndef LISTGAMESCOMMAND_H_
#define LISTGAMESCOMMAND_H_

#include "Command.h"
#include <iostream>
#include "ReversiServer.h"

class ListGamesCommand: public Command
{
public:
	ReversiServer *server;
	ListGamesCommand(ReversiServer *server) {
		this->server = server;
	}
	~ListGamesCommand();

	virtual string execute(vector<string> args, int clientSocket)
	{
		cout << "in list games command" << endl;
		map<string, GameInfo>::iterator it;
		string list;

		for (it = server->games.begin(); it != server->games.end(); it++)
		{
			if (it->second.client2 == 0) // if game is joinable
				list += it->first + "\n";
		}

		return list;
	}
};

#endif /* LISTGAMESCOMMAND_H_ */
