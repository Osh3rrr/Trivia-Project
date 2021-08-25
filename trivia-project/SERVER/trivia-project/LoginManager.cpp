#include "LoginManager.h"

LoginManager::LoginManager()
{
	this->m_database = new SqliteDatabase();
}

bool LoginManager::signup(std::string username, std::string password, std::string email)
{
	return this->m_database->addNewUser(username, password, email);
}

bool LoginManager::login(std::string username, std::string password)
{
	if (this->m_database->doesPasswordMatch(username, password)) // if the given username and password is correct.
	{
		for (std::vector<LoggedUser>::iterator it = this->m_loggedUsers.begin(); it != this->m_loggedUsers.end(); it++) // running all over the logged users
		{
			if (!it->getUsername().compare(username)) // if the user already logged in.
			{
				return false;
			}
		}

		LoggedUser user(username); // creating new logged user.
		this->m_loggedUsers.push_back(user); // pushing the logged user to the vector.

		return true;
	}

	return false;
}

void LoginManager::logout(std::string username)
{
	for (int i = 0; i < this->m_loggedUsers.size(); i++) // runnig all over this connected users
	{
		if (!this->m_loggedUsers.at(i).getUsername().compare(username)) // if we found the username to logout.
		{
			this->m_loggedUsers.erase(this->m_loggedUsers.begin() + i); // removing the user from the connected users vector.
		}
	}
}
