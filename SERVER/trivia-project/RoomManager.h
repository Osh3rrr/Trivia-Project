#pragma once

#include <iostream>
#include <map>
#include "Room.h"

using std::map;

class RoomManager
{
public:
	void createRoom(LoggedUser creator, RoomData data);
	void deleteRoom(int ID);
	void addUserToRoom(LoggedUser user, int ID);
	void deleteUser(LoggedUser user, int roomId);
	GetRoomStateResponse getRoomState(int ID);
	vector<RoomData> getRooms();

	Room getSpecificRoom(int id);

private:
	map<int, Room> m_rooms;
};
