#include "Controller.h"

// add methods to command hashtable
Controller::Controller ()
{
    commands["clear"] =  &Controller::clear;
    commands["help"]  =  &Controller::help;
    commands["add"]   =  &Controller::add;
    commands["print"] =  &Controller::print;
    commands["erase"] =  &Controller::erase;
    commands["test"]  =  &Controller::test;
    commands["empty"] =  &Controller::empty;
    commands["change"] =  &Controller::change;
}


void Controller::processCommand ()
{
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
        (this->*commands[key])(args); // run command
    } else {
        std::cout << "Command " << key << " not found. Please, check spelling or write \"help\"." << std::endl;
    }
}

vector<string> Controller::splitArguments(string strArgs)
{
    vector<string> args {};
    string line { "" };
    bool inQuotes { 0 };
    
    for (int i = 0; i <= strArgs.length(); ++i) {
        char ch { strArgs[i] };

        if (ch == '"') {
            inQuotes = !inQuotes;
        }

        // in quotes we get all words like one arguments
        if (inQuotes) {
            if (ch != '"') {
                line += ch;
            } 
        } else {
            // add argument to args list when word or sentence in quotes ends
            if (ch == ' ' or ch == '"' or ch == strArgs[strArgs.length()]) {
                if (line != "") {
                    args.push_back(line);
                    line = "";
                }
            }
            if (ch != ' ' and ch != '"') {
                line += ch;
            }
        }
    }

    return args;
}

int Controller::getWordId (string name)
{
    // user can find by word id or by name

    // if he write a number it just converted to integer
    try {
        return std::stoi(name)-1;
    }
    // but if it not a number, we catch convert error and find words id by name
    catch (std::invalid_argument const& ex) {
        json dict { Dictionary::GetDictionary() };
        int id { 0 };
        for (auto& word : dict[0]) {
            if (word["name"] == name) {
                return id;
            }
            id++;
        }
        std::cout << "Not found" << std::endl;
        return -1; // if noting found return -1 code
    }

}

void Controller::help (vector<string> args)
{
    if (args[0] == "") {
        std::cout << "help   - Write this text" << std::endl;
        std::cout << "add    - Add word to dictionary" << std::endl;
        std::cout << "clear  - Clear your terminal" << std::endl;
        std::cout << "print  - Print whole dictionary" << std::endl;
        std::cout << "test   - Testing your knowledge" << std::endl;
        std::cout << "empty  - Emptying your dictionary" << std::endl;
        std::cout << "change - Changing some information in word" << std::endl;
        std::cout << "/nFor more information: help <command name>" << std::endl;
    }
    
    if (args[0] == "add") {
        std::cout << "add <word> <translate> - simply add word with translation" << std::endl;
        std::cout << "add <word> <translate> \"<description>\""
            << " - add word with translation and description" << std::endl;
        std::cout << "add <word> <translate> \"<description>\" <first synonym> <second synonym> ... <last synonym>"
            << "\n - add word with translation, description and synonyms" << std::endl;
    }

    if (args[0] == "print") {
        std::cout << "print <id>   - show detail information" << std::endl;
        std::cout << "print <name> - show detail information" << std::endl;
    }

    if (args[0] == "test") {
        std::cout << "test <type>              - to start test" << std::endl;
        std::cout << "test <type> <difficulty> - to start test with specific difficulty" << std::endl;

        std::cout << "types:" << std::endl;
        std::cout << "wt - shows you the word, and you then write the translation" << std::endl;
        std::cout << "tw - shows you the translation, and you then write the word" << std::endl;

        std::cout << "difficulty:" << std::endl;
        std::cout << "1 - easy       - 30\% of words"  << std::endl;
        std::cout << "2 - normal     - 50\% of words"  << std::endl;
        std::cout << "3 - hard       - 80\% of words"  << std::endl;
        std::cout << "4 - impossible - 100\% of words" << std::endl;
    }

    if (args[0] == "change") {
        std::cout << "change <word index> <key> <value> - to change value in word" << std::endl;
        std::cout << "Keys:"       << std::endl;
        std::cout << "        name"        << std::endl;
        std::cout << "    translation" << std::endl;
        std::cout << "    synonym"     << std::endl;
        std::cout << "    synonyms"    << std::endl;
        std::cout << "    description" << std::endl;

        std::cout << "Specific keys command:" << std::endl;
        std::cout << "    change <word index> description \"<value>\" - to change description" << std::endl;
        std::cout << "    change <word index> synonym <index> <value> - to change concreted synonym" << std::endl;
        std::cout << "    change <word index> synonyms <first synonym> <second synonym> ... <last synonym> - to change all synonyms" << std::endl;
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

void Controller::print (vector<string> args)
{
    if (args[0] == "") {
        Dictionary::Print();   
    } else {
        int id { getWordId(args[0]) };
        // -1: not found
        if (id != -1) { 
            Dictionary::Print(id);
        }
    }
}

void Controller::add (vector<string> args)
{
    if (args[0] == "") {
        std::cout << "Please, check spelling or write \"help add\"." << std::endl;
        return;
    }

    if (args.size() == 2) {
        Dictionary::AddWord(args[0], args[1]);
    }
    if (args.size() == 3) {
        Dictionary::AddWord(args[0], args[1], args[2]);
    }
    if (args.size() > 3) {
        vector<string> synonyms {vector<string>(args.begin() + 3, args.end())};
        Dictionary::AddWord(args[0], args[1], args[2], synonyms);
    }
}

void Controller::erase (vector<string> args)
{
    // TODO change to getWordId func
    Dictionary::EraseWord(std::stoi(args[0])-1);
}

void Controller::test (vector<string> args)
{
    int difficulty { Normal };


    if (args[0] == "") {
        std::cout << "Please, check spelling or write \"help test\"." << std::endl;
        return;
    }

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
            // TODO add this to help
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

void Controller::change (vector<string> args)
{
    int wordId { getWordId(args[0]) };
    // -1: not found
    if (wordId != -1) {    
        if (args[0] == "" or args[1] == "" or args[2] == "") {
            std::cout << "Please, check spelling or write \"help change\"." << std::endl;
            return;
        }
            
        if ( args[1] == "name" or args[1] == "translation"
          or args[1] == "description"
          or args[1] == "synonym" or args[1] == "synonyms"
           ) 
        {
            if (args[1] == "synonym") {
                Dictionary::ChangeWord(wordId, std::stoi(args[2])-1, args[3]);
            }
            if (args[1] == "synonyms") {
                vector<string> synonyms {vector<string>(args.begin() + 2, args.end())};
                Dictionary::ChangeWord(wordId, args[1], synonyms);
            }
            if (args[1] != "synonym" and args[1] != "synonyms") {
                Dictionary::ChangeWord(wordId, args[1], args[2]);
            }
        } else {
            std::cout << "Wrong key" << std::endl;
        }
    }
}

Controller::~Controller ()
{

}