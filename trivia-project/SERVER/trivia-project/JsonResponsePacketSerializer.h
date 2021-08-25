#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "Responeses.h"
#include <iostream>
#include <vector>
#include "json.hpp"
#include <bitset>

#define BYTE 8
#define CONVERT_TO_FOUR_BYTES 4
#define FOUR_BYTES 4
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
#define CLOSE_ROOM_CODE 111
#define START_GAME_CODE 112
#define GET_ROOM_STATE_CODE 113
#define LEAVE_ROOM_CODE 114


using nlohmann::json;

class JsonResponsePacketSerializer
{
public:
	//V1
	static std::vector<unsigned char> serializeResponse(ErrorResponse errorStruct);
	static std::vector<unsigned char> serializeResponse(LoginResponse loginStruct);
	static std::vector<unsigned char> serializeResponse(SignupResponse signupStruct);
	//V2
	static std::vector<unsigned char> serializeResponse(LogoutResponse logoutStruct);
	static std::vector<unsigned char> serializeResponse(GetRoomsResponse roomsStruct);
	static std::vector<unsigned char> serializeResponse(GetPlayersInRoomResponse playersStruct);
	static std::vector<unsigned char> serializeResponse(JoinRoomResponse joinRoomStruct);
	static std::vector<unsigned char> serializeResponse(CreateRoomResponse createRoomStruct);
	static std::vector<unsigned char> serializeResponse(getHighScoreResponse statisticsStruct);
	static std::vector<unsigned char> serializeResponse(getPersonalStatusResponse statisticsStruct);
	//V3
	static std::vector<unsigned char> serializeResponse(CloseRoomResponse joinRoomStruct);
	static std::vector<unsigned char> serializeResponse(StartGameResponse joinRoomStruct);
	static std::vector<unsigned char> serializeResponse(GetRoomStateResponse joinRoomStruct);
	static std::vector<unsigned char> serializeResponse(LeaveRoomResponse joinRoomStruct);

private:
	static string vector_to_string(vector<string> strings_vector);
};
