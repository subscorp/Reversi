
#pragma once

#include "Command.h"
#include "ReversiServer.h"
#include <iostream>

class CloseCommand: public Command
{
public:
	ReversiServer *server;
	CloseCommand(ReversiServer* server);
	virtual string execute(vector<string> args, int clientSocket);
};
