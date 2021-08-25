#include "Question.h"

Question::Question()
{
}

Question::Question(std::string question, std::vector<std::string> answers)
{
    this->m_possibleAnswers = answers;
    this->m_question = question;
}

std::string Question::getQuestion()
{
    return this->m_question;
}

std::vector<std::string> Question::getPossibleAnswers()
{
    return this->m_possibleAnswers;
}

std::string Question::getCorrectAnswer()
{
    return this->m_possibleAnswers[CORRECT_ANSWER_INDEX];
}
