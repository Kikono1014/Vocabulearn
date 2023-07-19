#include "Controller.h"

// add methods to command table
Controller::Controller ()
{
    commands["clear"] =  &Controller::clear;
    commands["help"]  =  &Controller::help;
    commands["add"]   =  &Controller::add;
    commands["print"] =  &Controller::print;
    commands["erase"] =  &Controller::erase;
    commands["empty"] =  &Controller::empty;
}


void Controller::processCommand ()
{
    // get input from user
    string command { Key::GetString() };
    
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
        std::cout << "help   -  Write this text" << std::endl;
        std::cout << "clear  -  Clear your terminal" << std::endl;
        std::cout << "print  -  Print whole dictionary" << std::endl;
        std::cout << "add    -  Add word to dictionary(For more information: \"help add\")" << std::endl;
    }
    
    if (args[0] == "add") {
        std::cout << "add <word> <translate> - to simply add word and translation" << std::endl;
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

void Controller::empty (vector<string> args)
{
    Dictionary::Empty();
}

Controller::~Controller ()
{

}