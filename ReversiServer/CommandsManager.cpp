#include "CommandsManager.h"
#include "PrintCommand.h"
#include "StartCommand.h"
#include "ListGamesCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "CloseCommand.h"

CommandsManager::CommandsManager()
{
	//commandsMap["print"] = new PrintCommand();
	commandsMap["start"] = new StartCommand();
	commandsMap["list_games"] = new ListGamesCommand();
	commandsMap["join"] = new JoinCommand();
	commandsMap["play"] = new PlayCommand();
	commandsMap["close"] = new CloseCommand();
}

void CommandsManager::executeCommand(string command, vector<string> args)
{
	if (commandsMap.count(command) > 0) {
		cout << "Running command "<<command<<endl;
		Command *commandObj = commandsMap[command];
		commandObj->execute(args);
	}
	else {
		cout <<"Command not exist" << endl;
	}
}

CommandsManager::~CommandsManager()
{
	map<string, Command *>::iterator it;
	for (it = commandsMap.begin(); it != commandsMap.end(); it++)
	{
		delete it->second;
	}
}

