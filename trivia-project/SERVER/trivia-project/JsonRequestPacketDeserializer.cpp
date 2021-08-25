#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(char* buffer)
{
    LoginRequest login_request;
    json login_json = json::parse(string(buffer));

    login_request.username = login_json["username"];
    login_request.password = login_json["password"];

    return login_request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(char* buffer)
{
    SignupRequest signup_request;
    json signup_json = json::parse(string(buffer));

    signup_request.username = signup_json["username"];
    signup_request.password = signup_json["password"];
    signup_request.email = signup_json["email"];

    return signup_request;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(char* buffer)
{
    GetPlayersInRoomRequest get_players_request;
    json get_players_request_json = json::parse(string(buffer));

    get_players_request.roomId = get_players_request_json["roomId"];

    return get_players_request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(char* buffer)
{
    JoinRoomRequest join_room_request;
    json join_room_request_json = json::parse(string(buffer));
    
    join_room_request.roomId = join_room_request_json["roomId"];

    return join_room_request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(char* buffer)
{
    CreateRoomRequest create_room_request;
    json create_room_request_json = json::parse(string(buffer));

    create_room_request.roomName = create_room_request_json["roomName"];
    create_room_request.maxUsers = create_room_request_json["maxUsers"];
    create_room_request.questionCount = create_room_request_json["questionCount"];
    create_room_request.asnwerTimeout = create_room_request_json["answerTimeout"];

    return create_room_request;
}
