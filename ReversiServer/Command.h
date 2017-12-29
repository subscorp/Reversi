#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>
using namespace std;
class Command
{
	public:
		virtual void execute(vector<string> args) = 0;
		virtual ~Command() {}
};

#endif
