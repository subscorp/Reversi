#ifndef PRINTCOMMAND_H
#define PRINTCOMMAND_H

#include "Command.h"
#include <iostream>
class PrintCommand: public Command
{
	public:

	PrintCommand();
	virtual void execute(vector<string> args)
	{
		for (int i = 0; i < args.size(); i++)
		{
			cout << args[i] << " ";
		}
		cout << endl;
		cout << "in print command" << endl;

	}
};

#endif
