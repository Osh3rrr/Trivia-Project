#pragma once

#include <iostream>
#include <vector>
#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include <iostream>
#include "Responeses.h"
#include "JsonRequestPacketDeserializer.h"
#include "LoginManager.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory* handler);
	bool isRequestRelevant(RequestInfo req);
	RequestResult handleRequest(RequestInfo req);

private:
	RequestResult login(RequestInfo req);
	RequestResult signup(RequestInfo req);

	LoginManager* m_loginManager;
	RequestHandlerFactory* m_handlerFactory;

	std::vector<std::string> loggedUser;
};
