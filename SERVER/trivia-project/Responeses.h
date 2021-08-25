#pragma once

#include <string>
#include <vector>
#include "RoomData.h"
#include "StatisticsManager.h"

using std::vector;

typedef struct LoginResponse
{
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
} SignupResponse;

typedef struct ErrorResponse
{
	std::string message;
} ErrorResponse;

typedef struct LogoutResponse
{
	unsigned int status;
} LogoutResponse;

typedef struct GetRoomsResponse
{
	unsigned int status;
	vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	vector<string> players;
} GetPlayersInRoomResponse;

typedef struct getHighScoreResponse
{
	unsigned int status;
	vector<string> statistics;
} getHighScoreResponse;

typedef struct getPersonalStaticsResponse
{
	unsigned int status;
	stats statistics;
} getPersonalStatusResponse;

typedef struct JoinRoomResponse
{
	unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned int status;
} CreateRoomResponse;

typedef struct CloseRoomResponse
{
	unsigned int status;
} CloseRoomResponse;

typedef struct StartGameResponse
{
	unsigned int status;
} StartGameResponse;

typedef struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	vector<string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
} GetRoomStateResponse;

typedef struct LeaveRoomResponse
{
	unsigned int status;
} LeaveRoomResponse;
