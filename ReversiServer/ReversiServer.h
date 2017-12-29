
#pragma once
#include <vector> //new
#include <string> // new
#include <map> // new
using namespace std; // new


class ReversiServer
{

public:
	ReversiServer(int port);
	void start();
	void stop();
	map<string, int> games; //new

private:
	int port;
	int serverSocket; // the socket's file descriptor

	int handleClient(int clientSocket, int clientSocket2);
};

