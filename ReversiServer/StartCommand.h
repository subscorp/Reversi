
#ifndef STARTCOMMAND_H_
#define STARTCOMMAND_H_

#include "Command.h"
#include <iostream>
#include <string>
#include <map>
#include "ReversiServer.h"


class StartCommand: public Command
{
public:
	ReversiServer *server;
	StartCommand(ReversiServer *server)
	{
		this->server = server;
	}
	~StartCommand();

	virtual string execute(vector<string> args, int clientSocket)
	{
		if (args.size() < 2)
			return "";

		cout << "in start command" << endl;
		string name = args[1];
		cout << "creating a game named " << name << endl;

		if (server->games.count(name) > 0)
		{
			return "Error: game name exists";
		}
		GameInfo game;
		game.client1 = clientSocket;
		game.client2 = 0;
		server->games[name] = game;
		return "";
	}
};

#endif /* STARTCOMMAND_H_ */
