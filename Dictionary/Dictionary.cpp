#include "Dictionary.h"
Dictionary::Dictionary ()
{
    
}

void Dictionary::TryParseJson ()
{
    try
    {
        std::ifstream f("../dictionary.json");
        json dict { json::parse(f) };
    }
    catch (json::parse_error& ex) // create a json template
    {
        if (ex.byte == 1) {
            std::ifstream f("../dictionary.json");
            writeToJson(json::parse(R"([])"));
        }
    }
}

json Dictionary::readFromJson ()
{
    std::ifstream f("../dictionary.json");
    return json::parse(f);
}

void Dictionary::writeToJson (json dict)
{
    std::ofstream o("../dictionary.json");
    o << std::setw(4) << dict;
}

void Dictionary::AddWord (string name, string translation, string descriptions, vector<string> synonyms)
{
    json dict { readFromJson() }; 
    dict = dict[0];

    json word {
        {"name", name},
        {"translation", translation},
        {"score", 0},
        {"synonyms", synonyms},
        {"description", descriptions}
    };
    
    dict.push_back(word);
    
    writeToJson(dict);
}

void Dictionary::EraseWord (int pos)
{
    json dict { readFromJson() };
    dict = dict[0];
    dict.erase(pos);
    writeToJson(dict);
    
}

void Dictionary::Print ()
{
    json dict { readFromJson() };
    int p { 1 };
    for (auto& word : dict[0]) {
        std::cout << p << ":" << std::endl;
        std::cout << "    " << word["name"]        << std::endl;
        std::cout << "    " << word["translation"] << std::endl;

        p++;
    }
}

void Dictionary::Print (int id)
{
    json dict { readFromJson() };
    if (id < dict[0].size()) {
        json word { dict[0][id] };
        word = word [0];
        std::cout << "Word:        " << word["name"]        << std::endl;
        std::cout << "Translation: " << word["translation"] << std::endl;
        std::cout << "Description: " << word["description"] << std::endl;
        std::cout << "Synonyms: " << std::endl;
        for (auto& synonym : word["synonyms"]) {
            std::cout << "             " << synonym << std::endl;
        }
        std::cout << "Score:       " << word["score"] << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }
}

json Dictionary::GetDictionary ()
{
    return readFromJson();
}

void Dictionary::Empty ()
{
    writeToJson(json::parse(R"([])"));
}


void Dictionary::ChangeWord (int id, string key, string value)
{
    json dict { readFromJson() };
    dict = dict[0];
    dict[id][key] = value;
    writeToJson(dict);
}

void Dictionary::ChangeWord (int id, int synonymId, string value)
{
    json dict { readFromJson() };
    dict = dict[0];
    dict[id]["synonyms"][synonymId] = value;
    writeToJson(dict);
}

void Dictionary::ChangeWord (int id, string key, vector<string> values)
{
    json dict { readFromJson() };
    dict = dict[0];
    dict[id]["synonyms"] = values;
    writeToJson(dict);
}

Dictionary::~Dictionary ()
{
    
}