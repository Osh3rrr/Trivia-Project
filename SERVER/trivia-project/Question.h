#pragma once

#include <string>
#include <vector>
#include <map>

#define CORRECT_ANSWER_INDEX 1

class Question
{
	private:
		std::string m_question;
		std::vector<std::string> m_possibleAnswers;

	public:
		Question();
		Question(std::string question, std::vector<std::string> answers);

		std::string getQuestion();
		std::vector<std::string> getPossibleAnswers();
		std::string getCorrectAnswer();
};