#pragma once

#include <iostream>
#include <vector>

class IRequestHandler;

using std::string;

typedef struct LoginRequest
{
	string username;
	string password;
} LoginRequest;

typedef struct SignupRequest
{
	string username;
	string password;
	string email;
} SignupRequest;

typedef struct RequestInfo
{
	int id;
	std::string recivalTime;
	char* buffer;
} RequestInfo;

typedef struct RequestResult
{
	std::vector<unsigned char> response;
	IRequestHandler* newHandler;
} RequestResult;

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;
} GetPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomId;
} JoinRoomRequest;

typedef struct CreateRoomRequest
{
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int asnwerTimeout;
} CreateRoomRequest;
