
#pragma once

#include "Command.h"
#include <iostream>
#include <string>
#include <map>
#include "ReversiServer.h"


class StartCommand: public Command
{
public:
	ReversiServer *server;
	StartCommand(ReversiServer *server);
	virtual string execute(vector<string> args, int clientSocket);
};
