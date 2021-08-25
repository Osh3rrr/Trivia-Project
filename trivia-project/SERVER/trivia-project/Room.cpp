#include "Room.h"

Room::Room(RoomData data)
{
	m_metadata = data;
}

void Room::addUser(LoggedUser user)
{
	m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	for (size_t i = 0; i < m_users.size(); i++)
	{
		if (!m_users.at(i).getUsername().compare(user.getUsername()))
		{
			m_users.erase(m_users.begin() + i);
		}
	}
}

vector<string> Room::getAllUsers()
{
	vector<string> users;
	for (size_t i = 0; i < m_users.size(); i++)
	{
		users.push_back(m_users[i].getUsername());
	}
	return users;
}

unsigned int Room::getIsActive()
{
	return m_metadata.isActive;
}

RoomData Room::getData()
{
	return m_metadata;
}

GetRoomStateResponse Room::getRoomState()
{
	GetRoomStateResponse state;
	vector<string> players;
	for (auto player : this->m_users)
	{
		players.push_back(player.getUsername());
	}
	state.players = players;
	state.hasGameBegun = this->m_metadata.isActive;
	state.answerTimeout = this->m_metadata.timePerQuestion;
	state.questionCount = TEN_QUESTIONS;
	state.status = 1;
	return state;
}
