/******************************************
*Ori Hirshfeld
*201085776
******************************************/

#include "ReversiServer.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "CommandsManager.h"

using namespace std;

int main()
{
	ReversiServer server(8881);
	try {
		server.start();
	} catch (const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		exit(-1);
	}
}
