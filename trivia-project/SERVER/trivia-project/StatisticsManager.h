#pragma once

#include <vector>
#include <iostream>
#include "IDatabase.h"

typedef struct stats 
{
	int answerCount;
	int correctCount;
	int gamesPlayed;
	int score;
	float avargeTime;
} playerStats;

class StatisticsManager
{
	private:
		IDatabase* m_database;

	public:
		StatisticsManager(IDatabase* m_database);
		std::vector<std::string> getHighScore();
		playerStats getUserStatistics(std::string username);
};