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


class Testing
{
private:
    static vector<int> createTest  (json dict, int type);
    static void        doTest      (json dict, vector<int> test);
    static void        showResults (json dict, map<int, bool> results);

public:
    Testing();

    static void runTest (json dict, int type);

    ~Testing();

};

#endif