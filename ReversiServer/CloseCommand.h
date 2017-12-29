/*
 * CloseCommand.h
 *
 *  Created on: Dec 29, 2017
 *      Author: ori
 */

#ifndef CLOSECOMMAND_H_
#define CLOSECOMMAND_H_

#include "Command.h"
#include <iostream>

class CloseCommand: public Command
{
public:
	CloseCommand();
	virtual void execute(vector<string> args)
	{
		for (int i = 0; i < args.size(); i++)
		{
			cout << args[i] << " ";
		}
		cout << endl;
		cout << "in close command" << endl;

	}
};

#endif /* CLOSECOMMAND_H_ */
