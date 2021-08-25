#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory* handler)
{
	m_handlerFactory = handler;
	m_loginManager = handler->getLoginManager();
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo req)
{
	return req.id == LOGIN_REQUEST || req.id == SIGNUP_REQUEST;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo req)
{
	RequestResult res;

	if (req.id == LOGIN_REQUEST) // if the given request is to login
	{
		res = login(req);
	}
	else if (req.id == SIGNUP_REQUEST) // if the given request is to signup
	{
		res = signup(req);
	}

	return res;
}

/*
* The function will get a request, then he will login the client by the given values in the struct.
*/
RequestResult LoginRequestHandler::login(RequestInfo req)
{
	LoginResponse response;
	RequestResult request_result;
	LoginManager* manager = m_handlerFactory->getLoginManager();
	LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(req.buffer);

	response.status = manager->login(request.username, request.password);
	request_result.response = JsonResponsePacketSerializer::serializeResponse(response); //Making serialized response to be sent

	if (response.status) //If successful login - go to menu. Else - login again.
	{
		request_result.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_handlerFactory, LoggedUser(request.username));
	}
	else
	{
		request_result.newHandler = m_handlerFactory->createLoginRequestHandler(m_handlerFactory);
	}

	return request_result;
}

RequestResult LoginRequestHandler::signup(RequestInfo req)
{
	SignupResponse response;
	RequestResult request_result;
	LoginManager* manager = m_handlerFactory->getLoginManager();
	SignupRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(req.buffer);

	response.status = manager->signup(request.username, request.password, request.email);
	request_result.response = JsonResponsePacketSerializer::serializeResponse(response); //Making serialized response to be sent

	request_result.newHandler = m_handlerFactory->createLoginRequestHandler(m_handlerFactory); //If successfully signed up - send user to login. Else send him to login/signup again.

	return request_result;
}
