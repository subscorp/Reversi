/******************************************
*Ori Hirshfeld
*201085776
******************************************/

#include "ReversiServer.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

int main()
{
	//reading from port number
	string portAsString;
	int portNumber;

	ifstream myfile("serverConnectionDetails.txt");
	if (myfile.is_open())
	{
		getline(myfile,portAsString);
		myfile.close();
	}
	else
		cout << "Unable to open file";

	portNumber = atoi(portAsString.c_str());
	ReversiServer server(portNumber);
	try {
		server.start();
		cout << "Enter exit to stop server" << endl;
		string str;
		cin >> str;
		if (str == "exit")
			server.stop();
	} catch (const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		exit(-1);
	}
}
