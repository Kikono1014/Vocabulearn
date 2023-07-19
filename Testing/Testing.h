#ifndef TESTING_H
#define TESTING_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../Dictionary/Dictionary.h"
#include "../lib/Key/Key.h"

using std::string;
using std::vector;
using std::map;

enum TestTypes {
    WordTranslation,
    TranslationWord
};

class Testing
{
private:
    static vector<int>    createTest  (json dict, int type);
    static map<int, bool> doTest      (json dict, vector<int> test);
    static void           showResults (json dict, map<int, bool> results);

public:
    Testing();

    static void runTest (json dict, int type);

    ~Testing();

};

#endif