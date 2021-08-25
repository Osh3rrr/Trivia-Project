#include "JsonResponsePacketSerializer.h"

/*
The function will build the serialized byte data of the message using the message code and json
*/
std::vector<unsigned char> buildBuffer(json messageData, int messageCode)
{
	long dataLength;
	unsigned char binaryMessageCode, binaryDataLength[FOUR_BYTES];
	std::vector<unsigned char> buffer; // this will be our buffer to return.
	unsigned char* binaryData;


	binaryMessageCode = (char)messageCode; // converting our message code to 1 byte.
	dataLength = messageData.dump().length();

	// Shifting our data length with bytes to convert the length to 4 bytes binary.
	binaryDataLength[0] = (dataLength >> 24) & 0xFF;
	binaryDataLength[1] = (dataLength >> 16) & 0xFF;
	binaryDataLength[2] = (dataLength >> 8) & 0xFF;
	binaryDataLength[3] = dataLength & 0xFF;

	dataLength++;
	binaryData = new unsigned char[sizeof(char) * (dataLength)]; // allocating memory for our data
	strcpy((char*)binaryData, (messageData.dump()).c_str()); // copying our json data to the char array.

	/*
	* Now we can push all our data to the buffer by the protocol.
	* First we will push our message code (1 byte), then we will push our data length (4 bytes), then our data.
	*/

	buffer.push_back(binaryMessageCode); // pushing our message code.

	for (int i = 0; i < FOUR_BYTES; i++) // running all over the binary length and pushing to the buffer.
	{
		buffer.push_back(binaryDataLength[i]);
	}

	for (int i = 0; i < dataLength; i++) // running all over the data and pushing to the buffer.
	{
		buffer.push_back(binaryData[i]);
	}

	delete[] binaryData; // removing the memory that we allocated.

	return buffer;
}

/*
This function will serialize an error response
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;

	messageData["status"] = 0;
	messageData["message"] = errorStruct.message;

	buffer = buildBuffer(messageData, ERROR_CODE);
	return buffer;
}

/*
This function will serialize a login response
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse loginStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;

	messageData["status"] = loginStruct.status;

	buffer = buildBuffer(messageData, LOGIN_CODE);
	return buffer;
}

/*
This function will serialize a signup response
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse signupStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;

	messageData["status"] = signupStruct.status;

	buffer = buildBuffer(messageData, SIGNUP_CODE);
	return buffer;
}

/*
This function will serialize a logout response
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;

	messageData["status"] = logoutStruct.status;

	buffer = buildBuffer(messageData, LOGOUT_CODE);
	return buffer;
}

/*
This function will serialize a login response
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse roomsStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;
	json data;
	json rooms_data;
	
	for (auto room : roomsStruct.rooms)
	{
		data["ID"] = std::to_string(room.id);
		data["name"] = room.name;
		data["timePerQuestion"] = room.timePerQuestion;
		data["numOfQuestion"] = room.numOfQuestionsInGame;
		data["maxPlayers"] = room.maxPlayers;

		rooms_data[std::to_string(room.id)] = data.dump();
	}

	messageData["status"] = roomsStruct.status;
	messageData["rooms"] = rooms_data.dump();

	buffer = buildBuffer(messageData, GET_ROOMS_CODE);
	return buffer;
}

/*
This function will serialize a get-players-in-room response
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse playersStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;

	messageData["players"] = vector_to_string(playersStruct.players);
	messageData["status"] = 1;

	buffer = buildBuffer(messageData, GET_PLAYERS_IN_ROOM_CODE);
	return buffer;
}

/*
This function will serialize a join-room response
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoomStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;

	messageData["status"] = joinRoomStruct.status;

	buffer = buildBuffer(messageData, JOIN_ROOM_CODE);
	return buffer;
}

/*
This function will serialize a create-room response
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;

	messageData["status"] = createRoomStruct.status;

	buffer = buildBuffer(messageData, CREATE_ROOM_CODE);
	return buffer;
}

/*
This function will serialize a get-high-score response
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(getHighScoreResponse statisticsStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;

	messageData["status"] = 1;
	messageData["statistics"] = vector_to_string(statisticsStruct.statistics);

	buffer = buildBuffer(messageData, GET_HIGH_SCORE_CODE);
	return buffer;
}


/*
The buffer will look like:
<GET_PLAYERS_IN_ROOM_CODE><msg_len><[statistics: 1 2 3...]>
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(getPersonalStatusResponse statisticsStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;

	messageData["status"] = 1;
	messageData["answerCount"] = statisticsStruct.statistics.answerCount;
	messageData["avargeTime"] = statisticsStruct.statistics.avargeTime;
	messageData["gamesPlayed"] = statisticsStruct.statistics.gamesPlayed;
	messageData["score"] = statisticsStruct.statistics.score;
	messageData["avargeTime"] = statisticsStruct.statistics.avargeTime;

	buffer = buildBuffer(messageData, GET_PERSONAL_STATUS_CODE);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse closeRoomStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;

	messageData["status"] = closeRoomStruct.status;

	buffer = buildBuffer(messageData, CREATE_ROOM_CODE);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(StartGameResponse startGameStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;

	messageData["status"] = startGameStruct.status;

	buffer = buildBuffer(messageData, CREATE_ROOM_CODE);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse getRoomStateStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;

	messageData["status"] = getRoomStateStruct.status;
	messageData["hasGameBegun"] = getRoomStateStruct.hasGameBegun;
	messageData["answerTimeout"] = getRoomStateStruct.answerTimeout;
	messageData["questionCount"] = getRoomStateStruct.questionCount;
	messageData["players"] = vector_to_string(getRoomStateStruct.players);

	buffer = buildBuffer(messageData, CREATE_ROOM_CODE);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse leaveRoomStruct)
{
	std::vector<unsigned char> buffer;
	json messageData;

	messageData["status"] = leaveRoomStruct.status;

	buffer = buildBuffer(messageData, CREATE_ROOM_CODE);
	return buffer;
}

string JsonResponsePacketSerializer::vector_to_string(vector<string> strings_vector)
{
	string str = "";

	for (string string_from_vector : strings_vector)
	{
		str += string_from_vector + " ";
	}

	if (str != "")
	{
		str.pop_back();
	}

	return str;
}
