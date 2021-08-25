#include "RoomMemberRequestHandler.h"

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo req)
{
    RequestResult res;
    LeaveRoomResponse resp;

    this->m_handlerFactory->getRoomManager()->deleteUser(this->m_user, this->m_room.getData().id); // removing the user from the room
    resp.status = 1;

    res.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_handlerFactory, this->m_user); // if the user left the room, the new handler is the menu.
    res.response = JsonResponsePacketSerializer::serializeResponse(resp);

    return res;
}

RequestResult RoomMemberRequestHandler::startGame(RequestInfo req)
{
    RequestResult res;
    StartGameResponse resp;

    resp.status = 1;

    // TO-DO : Finish this start game function, what does start game means?

    res.response = JsonResponsePacketSerializer::serializeResponse(resp);
    res.newHandler = this;

    return res;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo req)
{
    RequestResult res;
    GetRoomStateResponse resp = this->m_roomManager->getRoomState(this->m_room.getData().id);

    res.newHandler = this;
    res.response = JsonResponsePacketSerializer::serializeResponse(resp);

    return res;
}

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory* handler, LoggedUser& user, Room& room)
{
    this->m_handlerFactory = handler;
    this->m_roomManager = handler->getRoomManager();
    this->m_room = room;
    this->m_user = user;
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo req)
{
    return req.id == LEAVE_ROOM_CODE || req.id == START_GAME_CODE || req.id == GET_ROOM_STATE_CODE;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo req)
{
    RequestResult res;

    switch (req.id)
    {
    case LEAVE_ROOM_CODE:
        res = leaveRoom(req);
        break;

    case START_GAME_CODE:
        res = startGame(req);
        break;

    case GET_ROOM_STATE_CODE:
        res = getRoomState(req);
        break;
    }

    return res;
}
