
#pragma once

#include "Command.h"
#include <iostream>
#include "ReversiServer.h"

class ListGamesCommand: public Command
{
public:
	ReversiServer *server;
	ListGamesCommand(ReversiServer *server);
	virtual string execute(vector<string> args, int clientSocket);
};

