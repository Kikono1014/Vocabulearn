#ifndef TESTING_H
#define TESTING_H

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <map>
#include "../Dictionary/Dictionary.h"
#include "../lib/nlohmann_json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;
using std::string;
using std::vector;
using std::map;

enum TestTypes {
    WordTranslation,
    TranslationWord
};

enum TestDifficulties {
    Easy,
    Normal,
    Hard
};

int random (int min, int max);
int uniqueRandom (int min, int max, vector<int> array);

class Testing
{
private:
    static vector<int> createTest     (json dict, int difficult);
    static void        doTest         (json dict, vector<int> test, int type);
    static void        proccessAnswer (json word, string answer, int type);

public:
    Testing();

    static void runTest (json dict, int type, int difficult);

    ~Testing();

};

#endif