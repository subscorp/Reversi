#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>

using namespace std;

class Command
{
	public:
		virtual string execute(vector<string> args, int clientSocket) = 0;
		virtual ~Command() {}
};

#endif
