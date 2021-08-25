#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"
#include <thread>
#include "Request.h"
#include "Helper.h"
#include <ctime> 
#include <time.h>
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

#define PORT 12345
#define MSG_LEN 4

class Communicator
{
private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients; // this field will store all the clients socket and requests.
	RequestHandlerFactory* m_handlerFactory;

	void accept();
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);

public:
	Communicator(); // d'tor
	~Communicator(); // c'tor

	void startHandleRequests();
};
