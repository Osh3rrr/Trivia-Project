#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"
#define SUCCESS 1

unsigned int MenuRequestHandler::roomIdCount = 1;
unsigned int MenuRequestHandler::getRoomIdCount()
{
	return MenuRequestHandler::roomIdCount;
}

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RequestHandlerFactory* handlerFactory)
{
	this->m_handlerFactory = handlerFactory;
	this->m_user = user;
	this->m_statisticsManager = handlerFactory->getStatisticsManager();
	this->m_roomManager = handlerFactory->getRoomManager();
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo req)
{
    return req.id == CREATE_ROOM_CODE || req.id == GET_ROOMS_CODE || req.id == GET_PLAYERS_IN_ROOM_CODE || req.id == JOIN_ROOM_CODE || req.id == GET_STATISTICS_CODE || req.id == LOGOUT_CODE;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo req)
{
    RequestResult resp;

    switch (req.id)
    {
    case CREATE_ROOM_CODE:
		resp = this->createRoom(req);
		break;
	case GET_ROOMS_CODE:
		resp = this->getRooms(req);
		break;
	case GET_PLAYERS_IN_ROOM_CODE:
		resp = this->getPlayersInRoom(req);
		break;
	case JOIN_ROOM_CODE:
		resp = this->joinRoom(req);
		break;
	case GET_STATISTICS_CODE:
		resp = this->getPersonalStats(req);
		break;
	case GET_HIGH_SCORE_CODE:
		resp = this->getHighScore(req);
		break;
	case LOGOUT_CODE:
		resp = this->signout(req);
		break;

	default:
		std::cerr << "Bad request code!" << std::endl;
    }

	return resp;
}

RequestResult MenuRequestHandler::signout(RequestInfo req)
{
	LogoutResponse response;
	RequestResult res;
	LoginManager* loginM = this->m_handlerFactory->getLoginManager();
	loginM->logout(this->m_user.getUsername());
	response.status = SUCCESS;

	res.newHandler = nullptr;

	std::vector<unsigned char> resbuff = JsonResponsePacketSerializer::serializeResponse(response);
	res.response = resbuff;
	return res;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo req)
{
	GetRoomsResponse response;
	RequestResult res;
	RoomManager* roomM = this->m_handlerFactory->getRoomManager();
	std::vector<RoomData> rooms = roomM->getRooms();

	response.rooms = rooms;
	if (response.rooms.size() == 0)
	{
		response.status = 0;
	}
	else
	{
		response.status = SUCCESS;
	}

	res.response = JsonResponsePacketSerializer::serializeResponse(response);
	res.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_handlerFactory, this->m_user);
	return res;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo req)
{
	GetPlayersInRoomResponse response;
	RequestResult res;
	GetPlayersInRoomRequest request = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(req.buffer);
	RoomManager* roomM = this->m_handlerFactory->getRoomManager();

	response.players = roomM->getSpecificRoom(request.roomId).getAllUsers();
	res.response = JsonResponsePacketSerializer::serializeResponse(response);
	res.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_handlerFactory, this->m_user);
	return res;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo req)
{
	getPersonalStaticsResponse response;
	RequestResult res;
	StatisticsManager* statsM = this->m_handlerFactory->getStatisticsManager();

	response.statistics = statsM->getUserStatistics(this->m_user.getUsername());
	response.status = SUCCESS;
	res.response = JsonResponsePacketSerializer::serializeResponse(response);
	res.newHandler = this;
	return res;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo req)
{
	getHighScoreResponse response;
	RequestResult res;
	StatisticsManager* statsM = this->m_handlerFactory->getStatisticsManager();

	response.statistics = statsM->getHighScore();
	response.status = SUCCESS;
	res.response = JsonResponsePacketSerializer::serializeResponse(response);
	res.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_handlerFactory, this->m_user);
	return res;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo req)
{
	JoinRoomResponse response;
	RequestResult res;
	JoinRoomRequest request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(req.buffer);

	RoomManager* roomM = this->m_handlerFactory->getRoomManager();
	roomM->addUserToRoom(this->m_user, request.roomId);

	response.status = SUCCESS;
	res.response = JsonResponsePacketSerializer::serializeResponse(response);
	
	res.newHandler = (IRequestHandler*)this->m_handlerFactory->createRoomMemberRequestHandler(this->m_handlerFactory, this->m_user, roomM->getSpecificRoom(request.roomId));
	return res;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo req)
{
	CreateRoomResponse response;
	RequestResult res;
	CreateRoomRequest request = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(req.buffer);
	RoomManager* roomM = this->m_handlerFactory->getRoomManager();
	StatisticsManager* stats = this->m_handlerFactory->getStatisticsManager();

	std::vector<RoomData> roomsList = roomM->getRooms();

	for (std::vector<RoomData>::iterator it = roomsList.begin(); it != roomsList.end(); ++it)
	{
		if (!it->name.compare(request.roomName))
		{
			response.status = 0;

			res.response = JsonResponsePacketSerializer::serializeResponse(response);
			res.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_handlerFactory, this->m_user);
			
			return res;
		}
	}

	unsigned int id = getRoomIdCount();
	MenuRequestHandler::roomIdCount++;

	RoomData data = { id,request.roomName,request.maxUsers,request.asnwerTimeout,false };

	roomM->createRoom(this->m_user, data);
	response.status = SUCCESS;
	MenuRequestHandler::roomIdCount++;
	res.response = JsonResponsePacketSerializer::serializeResponse(response);
	res.newHandler = (IRequestHandler*)this->m_handlerFactory->createRoomAdminRequestHandler(this->m_handlerFactory, this->m_user, roomM->getSpecificRoom(id));

	return res;
}
