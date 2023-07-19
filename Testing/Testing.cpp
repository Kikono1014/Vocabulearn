#include "Testing.h"

Testing::Testing()
{

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


void Testing::runTest (json dict, int type)
{
    vector<int> test { createTest(dict, type) };
    map<int, bool> results { doTest(dict, test) };
    showResults(dict, results);
}

Testing::~Testing()
{

}