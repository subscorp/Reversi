/*
 * PlayCommand.h
 *
 *  Created on: Dec 29, 2017
 *      Author: ori
 */

#ifndef PLAYCOMMAND_H_
#define PLAYCOMMAND_H_

#include "Command.h"
#include <iostream>

class PlayCommand: public Command
{
public:
	PlayCommand();
	virtual void execute(vector<string> args)
	{
		for (int i = 0; i < args.size(); i++)
		{
			cout << args[i] << " ";
		}
		cout << endl;
		cout << "in play command" << endl;
	}
};

#endif /* PLAYCOMMAND_H_ */
