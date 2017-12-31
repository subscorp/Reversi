/******************************************
*Ori Hirshfeld
*201085776
******************************************/

#include "ReversiServer.h"
#include <iostream>
#include <stdlib.h>

#include <vector> //new
#include <string> //new
#include "CommandsManager.h" //new

using namespace std;

int main()
{
	ReversiServer server(8888);
	try {
		server.start();
	} catch (const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		exit(-1);
	}
}
