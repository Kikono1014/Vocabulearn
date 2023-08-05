#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include "../lib/nlohmann_json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;
using std::string;
using std::vector;

class Dictionary
{
private:
    static json readFromJson ();
    static void writeToJson  (json dict);

public:
    Dictionary ();
    static void TryParseJson ();
  
    static void AddWord       (string name = "", string translation = "",
                               string descriptions = "", vector<string> synonyms = {});
    static void EraseWord     (int pos);
    static void Print         ();
    static void Print         (int id);
    static json GetDictionary ();
    static void Empty         ();
    static void ChangeWord    (int id, string key, int value);
    static void ChangeWord    (int id, string key, string value);
    static void ChangeWord    (int id, int synonymId, string value);
    static void ChangeWord    (int id, string key, vector<string> values);
    
    
    ~Dictionary ();

};

#endif