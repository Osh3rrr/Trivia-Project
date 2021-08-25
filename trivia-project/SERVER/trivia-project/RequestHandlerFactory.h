#pragma once

#include "LoginManager.h"
#include "IDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "MenuRequestHandler.h"

class RoomMemberRequestHandler;
class RoomAdminRequestHandler;
class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler(RequestHandlerFactory* handler);
	MenuRequestHandler* createMenuRequestHandler(RequestHandlerFactory* handler, LoggedUser user);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(RequestHandlerFactory* handler, LoggedUser user, Room room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(RequestHandlerFactory* handler, LoggedUser user, Room room);
	LoginManager* getLoginManager();
	RoomManager* getRoomManager();
	StatisticsManager* getStatisticsManager();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager* m_roomManager;
	StatisticsManager* m_StatisticsManager;
};
