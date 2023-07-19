#include "Testing.h"

int random(int min, int max) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    int random = mersenne() % max + min;
    return random;
}

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
    vector<int> test { };
    // TODO difficult choosing by user
    int counter { 5 }; // placeholder

    for (int i = 0; i < counter; ++i) {
        test.push_back(random(0, dict.size()));
    }
    return test;
}

map<int, bool> Testing::doTest (json dict, vector<int> test)
{
    map<int, bool> results { };
    
    return results;
}

void Testing::showResults (json dict, map<int, bool> results)
{
    
}


Testing::~Testing()
{

}