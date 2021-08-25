#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* m_database)
{
    this->m_database = m_database;
}

/////////////////////////////////////////////TO COMPLETE/////////////////////////////////
std::vector<std::string> StatisticsManager::getHighScore()
{
    std::vector<std::string> s;
    return s;
}

playerStats StatisticsManager::getUserStatistics(std::string username)
{
    playerStats stats;

    stats.answerCount = m_database->getNumOfTotalAnswers(username);
    stats.avargeTime = m_database->getPlayerAverageAnswerTime(username);
    stats.correctCount = m_database->getNumOfCorrectAnswers(username);
    stats.gamesPlayed = m_database->getNumOfPlayerGames(username);
    stats.score = stats.answerCount;

    return stats;
}
