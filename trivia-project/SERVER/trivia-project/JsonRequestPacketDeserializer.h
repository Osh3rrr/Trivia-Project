#pragma once

#include "Request.h"
#include "json.hpp"

using json = nlohmann::json;
using std::vector;

class JsonRequestPacketDeserializer
{
	public:
		static LoginRequest deserializeLoginRequest(char* buffer);
		static SignupRequest deserializeSignupRequest(char* buffer);

		static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(char* buffer);
		static JoinRoomRequest deserializeJoinRoomRequest(char* buffer);
		static CreateRoomRequest deserializeCreateRoomRequest(char* buffer);
};
