#include "Server.h"


void Server::connectorThreadHandler()
{
	this->m_communicator.startHandleRequests();
}

void Server::run()
{
	std::string command;

	std::thread t_connector(&Server::connectorThreadHandler, this); // this thread will connect clients to the server.

	while (true)
	{
		std::cin >> command;

		if (command == EXIT_COMMAND) // if the admin wrote "EXIT" in the cmd, we exit and stop the code.
		{
			std::exit(0);
		}
	}
}
