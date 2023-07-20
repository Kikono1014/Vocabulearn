#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../Testing/Testing.h"
#include "../Dictionary/Dictionary.h"
#include "../lib/Key/Key.h"

using std::string;
using std::vector;
using std::map;


class Controller
{
private:
    string currentSpace { "main" };

    // hash table of pointer to command functions
    map<string, void (Controller::*)(vector<string> args)> commands {};

    // program commands
    void help   (vector<string> args);
    void clear  (vector<string> args);
    void print  (vector<string> args);
    void add    (vector<string> args);
    void erase  (vector<string> args);
    void test   (vector<string> args);
    void empty  (vector<string> args);
    void change (vector<string> args);

    void           runCommands   (string key, vector<string> args);
    vector<string> splitArguments(string strArgs);
    
public:
    Controller ();

    void processCommand ();
    vector<string> getCommandsList ();

    ~Controller ();

};

#endif