#pragma once

#include <iostream>
#include "Request.h"

#define LOGIN_REQUEST 101
#define SIGNUP_REQUEST 102
#define ERROR_REQUEST 103

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo req) = 0;
	virtual RequestResult handleRequest(RequestInfo req) = 0;

	//IRequestHandler();
	//virtual ~IRequestHandler() = 0;
};
