#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include "Server.h"
#include "WSAInitializer.h"

int main()
{
	WSAInitializer wsaInit;
	Server* mt_server = new Server();

	mt_server->run();

	delete mt_server;

	return 0;
}