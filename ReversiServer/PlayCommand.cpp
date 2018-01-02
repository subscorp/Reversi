
#include "PlayCommand.h"


PlayCommand::PlayCommand(ReversiServer *server)
{
	this->server = server;
}

string PlayCommand::execute(vector<string> args, int clientSocket)
{
	if (args.size() < 3)
	{
		cout << "Error in play" << endl;
		return "";
	}

	string msg = args[1] + " " +args[2];

	// find client game
	map<string, GameInfo>::iterator it;
	for (it = server->games.begin(); it != server->games.end(); it++)
	{
		int sendTo = 0; // socket

		if (it->second.client1 == clientSocket)
			sendTo = it->second.client2;
		else if(it->second.client2 == clientSocket)
			sendTo = it->second.client1;

		if (sendTo)
		{
			char buffer[BUFFER_SIZE] = {0};
			strcpy(buffer, msg.c_str());
			if(write(sendTo, buffer, BUFFER_SIZE) == -1)
			{
				cout << "Error writing response" << endl;
			}
			break;
		}
	} // for
	return "";
}
