
#ifndef JOINCOMMAND_H_
#define JOINCOMMAND_H_

#include "Command.h"
#include "ReversiServer.h"
#include <iostream>
#include <unistd.h>

class JoinCommand: public Command
{
public:
	ReversiServer *server;

	JoinCommand(ReversiServer *server)
	{
		this->server = server;
	}
	~JoinCommand();

	virtual string execute(vector<string> args, int clientSocket)
	{
		cout << "in join command" << endl;
		if (args.size() < 2)
			return "";

		string name = args[1];

		if (this->server->games.count(name) == 0)
		{
			return "Game does not exist!";
		}

		// game start
		GameInfo game = this->server->games[name];
		game.client2 = clientSocket;
		this->server->games[name] = game;

		char buffer[BUFFER_SIZE] = "start_x";
		if(write(game.client1, buffer, BUFFER_SIZE) == -1)
		{
			cout << "Error writing response" << endl;
		}

		return "start_o";
	}
};

#endif /* JOINCOMMAND_H_ */
