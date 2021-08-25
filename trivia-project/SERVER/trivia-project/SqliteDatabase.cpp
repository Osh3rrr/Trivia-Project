#include "SqliteDatabase.h"

int CountCallBack(void* num, int count, char** data, char** columns);
int PasswordCallBack(void* data, int argc, char** argv, char** azColName);
int QuestionsCallBack(void* data, int argc, char** argv, char** azColName);
int numCallBack(void* data, int argc, char** argv, char** azColName);

#define QUESTION_ONE {"What is the capital city of Israel?", "Jerusalem", "Tel-Aviv", "Eilat", "Haifa"}
#define QUESTION_TWO {"How many squares there is in chess board?", "204", "204", "32", "80"}
#define QUESTION_THREE {"When did the First World War started?", "1914", "1918", "1940", "1900"}
#define QUESTION_FOUR {"When did the First World War ended?", "1918", "1920", "1927", "1999"}
#define QUESTION_FIVE {"When was the State of Israel established?", "1948", "1949", "1945", "1946"}
#define QUESTION_SIX {"Who was Israel's first prime minister?", "David Ben Gurion", "Benjamin Netanyahu", "Beni Gantz", "Ariel Sharon"}
#define QUESTION_SEVEN {"What is the capital city of Russia", "Moscow", "New York", "Ashkelon", "London"}
#define QUESTION_EIGHT {"When was the United States established?", "1776", "1700", "1750", "1650"}
#define QUESTION_NINE {"How many people live in Israel?", "9 Million", "3 Million", "5 Million", "15 Million"}
#define QUESTION_TEN {"How many seconds are there in a minute", "60", "40", "30", "120"}
#define QUESTION_ELEVEN {"What is 1 + 1?", "2", "3", "4", "5"}

bool SqliteDatabase::sendSqlStatement(std::string sqlStatement)
{
    int res;
    char* errMessage = nullptr;


    res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);


    if (res != SQLITE_OK)
    {
        std::cout << errMessage << std::endl;
        return false;
    }

    return true;
}

void SqliteDatabase::insertQuestionsToTable(std::vector<std::vector<std::string>> vec)
{

    for (std::vector<std::vector<std::string>>::iterator it = vec.begin(); it != vec.end(); it++) // running all over the questions and answers
    {
        std::string sqlStatement = "INSERT INTO QUESTIONS(QUESTION, CORRECT_ANSWER, A_ANSWER, B_ANSWER, C_ANSWER) VALUES ('" + (*it)[0] + "','" + (*it)[1] + "','" + (*it)[2] + "','" + (*it)[3] + "','" + (*it)[4] + "');";
        sendSqlStatement(sqlStatement);
    }
}

SqliteDatabase::SqliteDatabase()
{
    std::string dbFileName = "triviaDB.sqlite";

    int doesFileExist = _access(dbFileName.c_str(), 0); // checking if the file exists

    int res = sqlite3_open(dbFileName.c_str(), &this->_db); // opening or creating the database.

    if (res != SQLITE_OK) // if the opening function failed
    {
        if (doesFileExist == DB_FILE_EXISTS)
        {
            std::cout << "Error with opening the database file\n";
        }

        else
        {
            std::cout << "Error with creating the database file\n";
        }
    }

    if (doesFileExist != DB_FILE_EXISTS)
    {
        std::vector<std::vector<std::string>> questions = {QUESTION_ONE,
                                                           QUESTION_TWO,
                                                           QUESTION_THREE,
                                                           QUESTION_FOUR,
                                                           QUESTION_FIVE,
                                                           QUESTION_SIX,
                                                           QUESTION_SEVEN,
                                                           QUESTION_EIGHT,
                                                           QUESTION_NINE,
                                                           QUESTION_TEN,
                                                           QUESTION_ELEVEN};

        sendSqlStatement("CREATE TABLE USERS (USERNAME TEXT NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);");

        sendSqlStatement("CREATE TABLE QUESTIONS (QUESTION TEXT, CORRECT_ANSWER TEXT, A_ANSWER TEXT, B_ANSWER TEXT, C_ANSWER TEXT);");

        sendSqlStatement("CREATE TABLE STATISTICS (USERNAME TEXT, NUM_ANSWERS INT, NUM_CORRECT_ANSWERS INT, AVERAGE_TIME FLOAT, GAMES_PLAYED INT, FOREIGN KEY(USERNAME) REFERENCES USERS(USERNAME));");

        insertQuestionsToTable(questions);
    }
}

bool SqliteDatabase::doesUserExist(std::string username)
{
    int numOfUsers = 0;
    std::string sqlStatement;
    char* errMessage = nullptr;

    sqlStatement = "SELECT COUNT(*) FROM USERS WHERE USERNAME = \"";
    sqlStatement.append(username);
    sqlStatement.append("\";");

    if (sqlite3_exec(this->_db, sqlStatement.c_str(), CountCallBack, &numOfUsers, &errMessage) != SQLITE_OK) // sending the statement, if the sending failed:
    {
        std::cout << errMessage;
        return false;
    }

    if (numOfUsers >= ONE_USER) // if the sending succeeded we checking if we have atleast one user with the given username.
    {
        return true;
    }

    return false; // if there is no given username
}

bool SqliteDatabase::doesPasswordMatch(std::string username, std::string clientSidePassword)
{
    std::string serverSidePassword;
    char* errMessage = nullptr;

    if (!doesUserExist(username)) // checking if the user exists:
    {
        std::cout << "The user does not exists.\n";
        return false;
    }

    std::string sqlStatemnt = "SELECT PASSWORD FROM USERS WHERE USERNAME = \""; // this will be our statement to send
    sqlStatemnt.append(username);
    sqlStatemnt.append("\";");

    if (sqlite3_exec(this->_db, sqlStatemnt.c_str(), PasswordCallBack, &serverSidePassword, &errMessage) != SQLITE_OK) // sending the request and checking if something failed.
    {
        std::cout << errMessage;
        return false;
    }

    if (serverSidePassword == clientSidePassword) // if the request didn't fail, we checking if the passwords matches.
    {
        return true; // returning that the password matches.
    }

    return false; // if the password don't matches.
}

bool SqliteDatabase::addNewUser(std::string username, std::string password, std::string email)
{
    std::string sqlStatement = "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) VALUES (\"";
    sqlStatement.append(username);
    sqlStatement.append("\", \"");
    sqlStatement.append(password);
    sqlStatement.append("\", \"");
    sqlStatement.append(email);
    sqlStatement.append("\");");

    if (doesUserExist(username)) // if the user already exists.
    {
        std::cout << "This username already taken.\n";
        return false;
    }

    else // if the user doesn't exist
    {
        sendSqlStatement(sqlStatement); // adding the user.
        std::cout << "The user added successfully.";
        return true;
    }
    
}

std::list<Question> SqliteDatabase::getQuestions()
{
    std::list<Question> questionsList;
    char* errMessage;

    std::string sqlStatement = "SELECT * FROM QUESTIONS;";

    if (sqlite3_exec(this->_db, sqlStatement.c_str(), QuestionsCallBack, &questionsList, &errMessage) != SQLITE_OK) // if there was an error with getting the questions.
    {
        std::cerr << "Error with getting the questions from the database.\n";
        std::cout << errMessage;
    }

    return questionsList;
}

float SqliteDatabase::getPlayerAverageAnswerTime(std::string username)
{
    char* errMessage = nullptr;
    float avgTime = 0;

    std::string sqlStatement = "SELECT AVERAGE_TIME FROM STATISTICS WHERE USERNAME = '";
    sqlStatement.append(username);
    sqlStatement.append("';");

    if (sqlite3_exec(this->_db, sqlStatement.c_str(), numCallBack, &avgTime, &errMessage) != SQLITE_OK)
    {
        std::cout << errMessage;
    }

    return avgTime;
}

int SqliteDatabase::getNumOfCorrectAnswers(std::string username)
{
    char* errMessage = nullptr;
    int correctAnswers = 0;

    std::string sqlStatement = "SELECT NUM_CORRECT_ANSWERS FROM STATISTICS WHERE USERNAME = '";
    sqlStatement.append(username);
    sqlStatement.append("';");

    if (sqlite3_exec(this->_db, sqlStatement.c_str(), numCallBack, &correctAnswers, &errMessage) != SQLITE_OK)
    {
        std::cout << errMessage;
    }

    return correctAnswers;
}

int SqliteDatabase::getNumOfTotalAnswers(std::string username)
{
    char* errMessage = nullptr;
    int totalAnswers = 0;

    std::string sqlStatement = "SELECT NUM_ANSWERS FROM STATISTICS WHERE USERNAME = '";
    sqlStatement.append(username);
    sqlStatement.append("';");

    if (sqlite3_exec(this->_db, sqlStatement.c_str(), numCallBack, &totalAnswers, &errMessage) != SQLITE_OK)
    {
        std::cout << errMessage;
    }

    return totalAnswers;
}

int SqliteDatabase::getNumOfPlayerGames(std::string username)
{
    char* errMessage = nullptr;
    int games = 0;

    std::string sqlStatement = "SELECT GAMES_PLAYED FROM STATISTICS WHERE USER_NAME = '";
    sqlStatement.append(username);
    sqlStatement.append("';");

    if (sqlite3_exec(this->_db, sqlStatement.c_str(), numCallBack, &games, &errMessage) != SQLITE_OK)
    {
        std::cout << errMessage;
    }

    return games;
}

int numCallBack(void* data, int argc, char** argv, char** azColName)
{
    float* returnVal = (float*)data; // converting the given pointer to float pointer.

    for (int i = 0; i < argc; i++)
    {
        (*returnVal) += std::stof(std::string(argv[i])); // converting the data to string then to float.
    }

    return 0;
}

int CountCallBack(void* data, int argc, char** argv, char** azColName)
{
    int* number = (int*)data; // making pointer to the given num.

    (*number) += std::stoi(std::string(argv[0])); // converting the number to int, then saving the number in the pointer value.

    return 0;
}

int PasswordCallBack(void* data, int argc, char** argv, char** azColName)
{
    std::string* password = (std::string*)data;

    *password = argv[0]; // the password 

    return 0;
}

int QuestionsCallBack(void* data, int argc, char** argv, char** azColName)
{
    int counter = 0;
    std::list<Question>* triviaQuestionsList = (std::list<Question>*)data;

    std::vector<std::string> triviaAnswers;
    std::string triviaQuestion;
    
    for (int i = 0; i < argc; i++)
    {
        counter++; // inc the counter to know where we at.
        
        if (std::string(azColName[i]) == "QUESTION") // if we are at the question
        {
            triviaQuestion = argv[i];
        }

        else // if we are on one of the possible answers
        {
            triviaAnswers.push_back(argv[i]);
        }

        if (counter == NEW_QUESTION) // if we need to push our question, and move to other question.
        {
            triviaQuestionsList->push_back(Question(triviaQuestion, triviaAnswers)); // pushing our question to the list, with the c'tor of question and all the required params.

            counter = 0; // resetting the counter to know we are on new question.
            triviaAnswers.clear(); // clearing the trivia answers because we are one new question now.
        }
    }

    return 0;
}