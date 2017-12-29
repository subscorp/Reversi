/*
 * ListGamesCommand.h
 *
 *  Created on: Dec 29, 2017
 *      Author: ori
 */

#ifndef LISTGAMESCOMMAND_H_
#define LISTGAMESCOMMAND_H_

#include "Command.h"
#include <iostream>

class ListGamesCommand: public Command
{
public:
	ListGamesCommand();
	virtual void execute(vector<string> args)
	{
		for (int i = 0; i < args.size(); i++)
		{
			cout << args[i] << " ";
		}
		cout << endl;
		cout << "in list games command" << endl;

	}
};

#endif /* LISTGAMESCOMMAND_H_ */
