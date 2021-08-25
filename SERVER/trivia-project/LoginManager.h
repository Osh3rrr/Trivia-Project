#pragma once

#include <iostream>
#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"
#include "SqliteDatabase.h"

class LoginManager
{
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;

public:
	LoginManager();
	bool signup(std::string, std::string, std::string);
	bool login(std::string, std::string);
	void logout(std::string);
};
