
#include "ListGamesCommand.h"


ListGamesCommand::ListGamesCommand(ReversiServer *server)
{
	this->server = server;
}

string ListGamesCommand::execute(vector<string> args, int clientSocket)
{
	string list;
	map<string, GameInfo>::iterator it;
	for (it = server->games.begin(); it != server->games.end(); it++)
	{
		if (it->second.client2 == 0) // if game is joinable
			list += it->first + "\n";
	}
	if (list.empty())
		return "\nNo Games available.\n";
	return "\n" + list;
}
