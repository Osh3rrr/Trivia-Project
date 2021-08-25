#include "RoomAdminRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo req)
{
    RequestResult res;
    CloseRoomResponse resp;

    resp.status = 1;
    
    this->m_roomManager->deleteRoom(this->m_room.getData().id);

    res.response = JsonResponsePacketSerializer::serializeResponse(resp);
    res.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_handlerFactory, this->m_user);

    return res;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo req)
{
    RequestResult res;
    StartGameResponse resp;

    resp.status = 1;
    
    // TO-DO

    res.response = JsonResponsePacketSerializer::serializeResponse(resp);
    res.newHandler = this;

    return res;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo req)
{
    RequestResult res;

    GetRoomStateResponse respo = this->m_roomManager->getRoomState(m_room.getData().id);
    respo.status = 1;

    res.response = JsonResponsePacketSerializer::serializeResponse(respo);
    res.newHandler = this;

    return res;
}

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory* handler, LoggedUser user, Room room)
{
    this->m_handlerFactory = handler;
    this->m_user = user;
    this->m_room = room;
    this->m_roomManager = handler->getRoomManager();
}

RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo req)
{
    return req.id == START_GAME_CODE || req.id == CLOSE_ROOM_CODE || req.id == GET_ROOM_STATE_CODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo req)
{
    RequestResult ret;

    switch (req.id)
    {
        case START_GAME_CODE:
            ret = startGame(req);
            break;

        case CLOSE_ROOM_CODE:
            ret = closeRoom(req);
            break;

        case GET_ROOM_STATE_CODE:
            ret = getRoomState(req);
            break;
    }

    return ret;
}
