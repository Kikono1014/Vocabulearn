#include "Testing.h"

Testing::Testing()
{

}

void Testing::runTest (json dict, int type)
{
    vector<int> test { createTest(dict, type) };
    map<int, bool> results { doTest(dict, test) };
    showResults(dict, results);
}

vector<int> Testing::createTest (json dict, int type)
{

}

map<int, bool> Testing::doTest (json dict, vector<int> test)
{

}

void Testing::showResults (json dict, map<int, bool> results)
{

}


Testing::~Testing()
{

}