#include "Dictionary.h"
Dictionary::Dictionary ()
{
    
}

json Dictionary::readfromJson ()
{
    std::ifstream f("../dictionary.json");
    json dict { };
    try
    {
        dict = json::parse(f) ;
    }
    catch (json::parse_error& ex)
    {
        if (ex.byte == 1) {
            json t { json::parse(R"([])") };
            writeToJson(t);
            dict = json::parse(f) ;
        }
    }
    
    return dict;
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
    json dict { readfromJson() };
    dict.erase(pos);
    writeToJson(dict);
    
}

void Dictionary::Print ()
{
    json dict { readfromJson() };
    int p { 1 };
    for (auto& i : dict) {
        std::cout << p << ":" << std::endl;
        std::cout << "    " << i["name"]        << std::endl;
        std::cout << "    " << i["translation"] << std::endl;
        std::cout << "    " << i["description"] << std::endl;

        p++;
    }
}

Dictionary::~Dictionary ()
{
    
}