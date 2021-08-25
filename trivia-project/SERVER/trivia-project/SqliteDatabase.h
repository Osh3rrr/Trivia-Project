#pragma once

#include <io.h>
#include <string>
#include "sqlite3.h"
#include "IDatabase.h"

#define DB_FILE_EXISTS 0
#define ONE_USER 1
#define NEW_QUESTION 5

class SqliteDatabase : public IDatabase
{
	private:
		sqlite3* _db;
		bool sendSqlStatement(std::string sqlStatement);
		void insertQuestionsToTable(std::vector<std::vector<std::string>> vec);

	public:
		SqliteDatabase(); // c'tor

		// Methods:
		bool doesUserExist(std::string username);
		bool doesPasswordMatch(std::string username, std::string clientSidePassword);
		bool addNewUser(std::string username, std::string password, std::string email);

		std::list<Question> getQuestions();
		float getPlayerAverageAnswerTime(std::string);
		int getNumOfCorrectAnswers(std::string);
		int getNumOfTotalAnswers(std::string);
		int getNumOfPlayerGames(std::string);
};
