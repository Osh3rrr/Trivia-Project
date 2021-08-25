#pragma once

#include "Communicator.h"
#include <thread>
#include <iostream>
#include <string>

#define EXIT_COMMAND "EXIT"

class Server
{
	private:
		Communicator m_communicator;
		void connectorThreadHandler();

	public:
		void run();
};
