#include "Controller.h"

// add methods to command table
Controller::Controller ()
{
    commands["clear"] =  &Controller::clear;
    commands["help"]  =  &Controller::help;
    commands["add"]   =  &Controller::add;
    commands["print"] =  &Controller::print;
    commands["erase"] =  &Controller::erase;
    commands["test"]  =  &Controller::test;
    commands["empty"] =  &Controller::empty;
}


void Controller::processCommand ()
{
    // get input from user
    string command { Key::GetAsyncString() };
    
    if (command != "") {
        string key { command };
        vector<string> args { "" };

        // if space exist
        if (command.find(" ") != string::npos) {
            // use first word like a key to command and other split to arguments array
            key  = command.substr(0, command.find(" "));
            string strArgs { command.substr(command.find(" ")+1, command.length() - key.length()) };
            args = splitArguments(strArgs);
        }
        runCommands(key, args);
    }
}

// give a list of commands name
vector<string> Controller::getCommandsList ()
{
    vector<string> commandsList {};

    for (auto key : commands) {
        commandsList.push_back(key.first);
    }
    return commandsList;
}

void Controller::runCommands (string key, vector<string> args) 
{
    if (commands.find(key) != commands.end()) {
        (this->*commands[key])(args);
    } else {
        std::cout << "Command " << key << " not found. Please, check spelling or write \"help\"." << std::endl;
    }
}

vector<string> Controller::splitArguments(string strArgs)
{
    vector<string> args {};
    string word { "" };
    for (int i = 0; i <= strArgs.length(); ++i) {
        if (strArgs[i] == ' ' or strArgs[i] == strArgs[strArgs.length()]) {
            args.push_back(word);
            word = "";
        }

        if (strArgs[i] != ' ') {
            word += strArgs[i];
        }
    }
    return args;
}


void Controller::help (vector<string> args)
{
    if (args[0] == "") {
        std::cout << "help  -  Write this text" << std::endl;
        std::cout << "clear -  Clear your terminal" << std::endl;
        std::cout << "print -  Print whole dictionary" << std::endl;
        std::cout << "add   -  Add word to dictionary (For more information: \"help add\")" << std::endl;
        std::cout << "test  -  Testing your knowledge (For more information: \"help test\")" << std::endl;
        std::cout << "empty -  Emptying your dictionary" << std::endl;
    }
    
    if (args[0] == "add") {
        std::cout << "add <word> <translate> - to simply add word and translation" << std::endl;
    }


    if (args[0] == "test") {
        std::cout << "test <type>              - to start test" << std::endl;
        std::cout << "test <type> <difficulty> - to start test with specific difficulty" << std::endl;

        std::cout << "types:" << std::endl;
        std::cout << "wt - shows you the word, and you then write the translation" << std::endl;
        std::cout << "tw - shows you the translation, and you then write the word" << std::endl;

        std::cout << "difficulty:" << std::endl;
        std::cout << "1 - easy       - 30\% of words" << std::endl;
        std::cout << "2 - normal     - 50\% of words" << std::endl;
        std::cout << "3 - hard       - 80\% of words" << std::endl;
        std::cout << "4 - impossible - 100\% of words" << std::endl;
    }

}

// clear terminal
void Controller::clear (vector<string> args)
{
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

// show whole dictionary
void Controller::print (vector<string> args)
{
    Dictionary::Print();
}

void Controller::add (vector<string> args)
{
    string name        = args[0];
    string translation = args[1];
    Dictionary::AddWord(name, translation);
}

void Controller::erase (vector<string> args)
{
    Dictionary::EraseWord(std::stoi(args[0])-1);
}

void Controller::test (vector<string> args)
{
    int difficulty { Normal };
    
    if (args.size() == 2) {
        if (args[1] == "easy") {
            difficulty = Easy;
        }
        if (args[1] == "normal") {
            difficulty = Normal;
        }
        if (args[1] == "hard") {
            difficulty = Hard;
        }
        if (args[1] == "impossible") {
            difficulty = Impossible;
        } else {
            difficulty = std::stoi(args[1])-1;
        }
    }

    if (args[0] == "wt") {
        Testing::runTest(Dictionary::GetDictionary(), WordTranslation, difficulty);
    }
    if (args[0] == "tw") {
        Testing::runTest(Dictionary::GetDictionary(), TranslationWord, difficulty); 
    }
}

void Controller::empty (vector<string> args)
{
    Dictionary::Empty();
}

Controller::~Controller ()
{

}