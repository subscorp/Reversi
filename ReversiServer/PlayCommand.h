
#pragma once

#include "Command.h"
#include "ReversiServer.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <string.h>

class PlayCommand : public Command
{
public:
	ReversiServer *server;
	PlayCommand(ReversiServer *server);
	virtual string execute(vector<string> args, int clientSocket);
};

