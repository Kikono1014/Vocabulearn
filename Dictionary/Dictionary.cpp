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
void Dictionary::AddWord (string name, string translation, vector<string> synonyms, string descriptions)
{
    std::ifstream f("../dictionary.json");
    json dict { json::parse(f) }; 
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
    dict.erase(pos);
    writeToJson(dict);
    
}

void Dictionary::Print ()
{
    json dict { readFromJson() };
    int p { 1 };
    for (auto& word : dict) {
        std::cout << p << ":" << std::endl;
        std::cout << "    " << word["name"]        << std::endl;
        std::cout << "    " << word["translation"] << std::endl;
        std::cout << "    " << word["description"] << std::endl;

        p++;
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

Dictionary::~Dictionary ()
{
    
}