
#include "StartCommand.h"


StartCommand::StartCommand(ReversiServer *server)
{
	this->server = server;
}

string StartCommand::execute(vector<string> args, int clientSocket)
{
	if (args.size() < 2)
		return "";

	string name = args[1];
	cout << "creating a game named " << name << endl;

	if (server->games.count(name) > 0)
	{
		return "\nError: game name exists.\n";
	}
	GameInfo game;
	game.client1 = clientSocket;
	game.client2 = 0;
	server->games[name] = game;
	return "";
}
