
#include "CloseCommand.h"


CloseCommand::CloseCommand(ReversiServer* server)
{
	this->server = server;
}

string CloseCommand::execute(vector<string> args, int clientSocket)
{
	cout << "in close command" << endl;
	return "";
}
