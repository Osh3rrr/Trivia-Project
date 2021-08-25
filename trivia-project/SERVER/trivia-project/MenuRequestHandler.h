#pragma once

#include "StatisticsManager.h"
#include "IRequestHandler.h"
#include "Responeses.h"
#include "RoomManager.h"
#include "JsonRequestPacketDeserializer.h"
#include "Room.h"
#include "JsonResponsePacketSerializer.h"

class RequestHandlerFactory;

#define LOGIN_CODE 101
#define SIGNUP_CODE 102
#define ERROR_CODE 103
#define LOGOUT_CODE 104
#define GET_ROOMS_CODE 105
#define JOIN_ROOM_CODE 106
#define GET_PLAYERS_IN_ROOM_CODE 107
#define CREATE_ROOM_CODE 108
#define GET_HIGH_SCORE_CODE 109
#define GET_PERSONAL_STATUS_CODE 110
#define GET_STATISTICS_CODE 111

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser user, RequestHandlerFactory* handlerFactory);

	bool isRequestRelevant(RequestInfo req);
	RequestResult handleRequest(RequestInfo req);

	static unsigned int getRoomIdCount();

private:
	LoggedUser m_user;
	RoomManager* m_roomManager;
	StatisticsManager* m_statisticsManager;
	RequestHandlerFactory* m_handlerFactory;

	RequestResult signout(RequestInfo req);
	RequestResult getRooms(RequestInfo req);
	RequestResult getPlayersInRoom(RequestInfo req);
	RequestResult getPersonalStats(RequestInfo req);
	RequestResult getHighScore(RequestInfo req);
	RequestResult joinRoom(RequestInfo req);
	RequestResult createRoom(RequestInfo req);

	static unsigned int roomIdCount;
};
