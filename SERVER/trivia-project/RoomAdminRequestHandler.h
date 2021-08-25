#pragma once

#include "IRequestHandler.h"
#include "RoomManager.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
private:
	Room m_room;
	LoggedUser m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory* m_handlerFactory;

	RequestResult closeRoom(RequestInfo req);
	RequestResult startGame(RequestInfo req);
	RequestResult getRoomState(RequestInfo req);

public:
	RoomAdminRequestHandler(RequestHandlerFactory* handler, LoggedUser user, Room room);
	~RoomAdminRequestHandler();
	bool isRequestRelevant(RequestInfo req);
	RequestResult handleRequest(RequestInfo req);
};