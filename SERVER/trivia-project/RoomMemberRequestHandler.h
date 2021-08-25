#pragma once

#include "IRequestHandler.h"
#include "RoomManager.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

class RoomMemberRequestHandler : public IRequestHandler
{
private:
	Room m_room;
	LoggedUser m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory* m_handlerFactory;

	RequestResult leaveRoom(RequestInfo req);
	RequestResult startGame(RequestInfo req);
	RequestResult getRoomState(RequestInfo req);

public:
	RoomMemberRequestHandler(RequestHandlerFactory* handler, LoggedUser& user, Room& room);
	bool isRequestRelevant(RequestInfo req);
	RequestResult handleRequest(RequestInfo req);
};
