#pragma once

#include <iostream>
#include <vector>
#include "LoggedUser.h"
#include "RoomData.h"
#include "Responeses.h"

#define TEN_QUESTIONS 10

using std::string;
using std::vector;

class Room
{
public:
	Room() = default;
	Room(RoomData data);
	~Room() = default;
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	vector<string> getAllUsers();
	unsigned int getIsActive();
	RoomData getData();
	GetRoomStateResponse getRoomState();

private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
};
