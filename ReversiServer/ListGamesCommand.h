
#ifndef LISTGAMESCOMMAND_H_
#define LISTGAMESCOMMAND_H_

#include "Command.h"
#include <iostream>
#include "ReversiServer.h"

class ListGamesCommand: public Command
{
public:
	ReversiServer *server;
	ListGamesCommand(ReversiServer *server)
	{
		this->server = server;
	}
	~ListGamesCommand();

	virtual string execute(vector<string> args, int clientSocket)
	{
		cout << "in list games command" << endl;

		string list;
		map<string, GameInfo>::iterator it;
		for (it = server->games.begin(); it != server->games.end(); it++)
		{
			if (it->second.client2 == 0) // if game is joinable
				list += it->first + "\n";
		}
		if (list.empty())
			return "No Games available.\n";
		return list;
	}
};

#endif /* LISTGAMESCOMMAND_H_ */
