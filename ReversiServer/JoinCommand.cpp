
#include "JoinCommand.h"


JoinCommand::JoinCommand(ReversiServer *server)
{
	this->server = server;
}


string JoinCommand::execute(vector<string> args, int clientSocket)
{
	cout << "in join command" << endl;
	if (args.size() < 2)
		return "";

	string name = args[1];

	if (this->server->games.count(name) == 0)
	{
		return "\nGame does not exist!\n";
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
