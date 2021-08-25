#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser creator, RoomData data)
{
	
	m_rooms.insert({ data.id, data }); //Even though I send data, it will be converted to Room(data) - see Room.h to understand.
	creator.changeUsername(creator.getUsername().append("-Admin"));
	this->m_rooms.at(data.id).addUser(creator);
}

void RoomManager::deleteRoom(int ID)
{
	m_rooms.erase(ID); //Will erase the pair (meaning both ID and room)
}

void RoomManager::addUserToRoom(LoggedUser user, int ID)
{
	this->m_rooms.at(ID).addUser(user);
}

void RoomManager::deleteUser(LoggedUser user, int roomId)
{
	this->m_rooms.at(roomId).removeUser(user);
}

GetRoomStateResponse RoomManager::getRoomState(int ID)
{
	if (this->m_rooms.find(ID) == this->m_rooms.end())
	{
		GetRoomStateResponse res;
		std::vector<std::string> closedRoom;
		closedRoom.push_back("");
		res.players = closedRoom;
		res.hasGameBegun = 0;
		res.questionCount = 0;
		res.answerTimeout = 0;
		res.status = 1;

		return res;
	}
	return this->m_rooms.at(ID).getRoomState(); //getIsActive returns the property "isActive" of the room.
}

vector<RoomData> RoomManager::getRooms()
{
	vector<RoomData> rooms;
	for (auto room : this->m_rooms) //Loops through all the rooms in the map and appending their data to the vector rooms
	{
		rooms.push_back(room.second.getData());
	}
	return rooms;
}

Room RoomManager::getSpecificRoom(int id)
{
	return this->m_rooms[id];
}
