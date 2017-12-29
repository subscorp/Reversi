/*
 * JoinCommand.h
 *
 *  Created on: Dec 29, 2017
 *      Author: ori
 */

#ifndef JOINCOMMAND_H_
#define JOINCOMMAND_H_

#include "Command.h"
#include <iostream>

class JoinCommand: public Command
{
public:
	JoinCommand();
	virtual void execute(vector<string> args)
	{
		for (int i = 0; i < args.size(); i++)
		{
			cout << args[i] << " ";
		}
		cout << endl;
		cout << "in join command" << endl;

	}
};

#endif /* JOINCOMMAND_H_ */
