
#pragma once

#include "Command.h"
#include "ReversiServer.h"
#include <iostream>
#include <unistd.h>

class JoinCommand: public Command
{
public:
	ReversiServer *server;
	JoinCommand(ReversiServer *server);
	virtual string execute(vector<string> args, int clientSocket);
};
