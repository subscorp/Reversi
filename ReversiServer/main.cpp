/******************************************
*Ori Hirshfeld
*201085776
*Amichai Wollin
*300582392
******************************************/

#include "ReversiServer.h"
#include <iostream>
#include <stdlib.h>

#include <vector>
#include <string>
#include "CommandsManager.h"

using namespace std;

int main()
{
	/*
	ReversiServer server(8882);
	try {
		server.start();
	} catch (const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		exit(-1);
	}
	*/

	vector<string> args;
	args.push_back("1");
	args.push_back("2");
	args.push_back("3");
	CommandsManager *manager = new CommandsManager();
	manager->executeCommand("start",args);
}
