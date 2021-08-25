#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory()
{
	this->m_loginManager = LoginManager();
	this->m_database = new SqliteDatabase();
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler(RequestHandlerFactory* handler)
{
	return new LoginRequestHandler(handler);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(RequestHandlerFactory* handler, LoggedUser user)
{
	return new MenuRequestHandler(user, handler);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(RequestHandlerFactory* handler, LoggedUser user, Room room)
{
	return new RoomAdminRequestHandler(handler, user, room);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(RequestHandlerFactory* handler, LoggedUser user, Room room)
{
	return new RoomMemberRequestHandler(handler, user, room);
}

LoginManager* RequestHandlerFactory::getLoginManager()
{
	return &m_loginManager;
}

RoomManager* RequestHandlerFactory::getRoomManager()
{
	if (this->m_roomManager == nullptr)
	{
		this->m_roomManager = new RoomManager();
	}

	return this->m_roomManager;
}

StatisticsManager* RequestHandlerFactory::getStatisticsManager()
{
	if (this->m_StatisticsManager == nullptr)
	{
		this->m_StatisticsManager = new StatisticsManager(this->m_database);
	}

	return this->m_StatisticsManager;
}
