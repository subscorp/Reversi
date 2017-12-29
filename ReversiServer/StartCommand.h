/*
 * StartCommand.h
 *
 *  Created on: Dec 29, 2017
 *      Author: ori
 */


#ifndef STARTCOMMAND_H_
#define STARTCOMMAND_H_

#include "Command.h"
#include <iostream>
#include <string>
#include <map>
#include "ReversiServer.h"

class StartCommand: public Command
{
public:
	StartCommand();
	virtual void execute(vector<string> args)
		{
			for (int i = 0; i < args.size(); i++)
			{
				cout << args[i] << " ";
			}
			cout << endl;
			cout << "in start command" << endl;

			string name = args[0];
			cout << name << endl;

			//games[name] = 1;



		}
};

#endif /* STARTCOMMAND_H_ */
