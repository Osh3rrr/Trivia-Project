#pragma once

#include <iostream>

class LoggedUser
{
	private:
		std::string m_username;

	public:
		LoggedUser() = default;
		LoggedUser(std::string username);
		std::string getUsername();
		void changeUsername(std::string username);
};