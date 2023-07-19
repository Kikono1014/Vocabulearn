#include "Testing.h"


int random (int min, int max) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    unsigned long rand { mersenne() % max + min} ;
    return rand;
}

int uniqueRandom (int min, int max, vector<int> array)
{
    int rand { random(min, max) };
    for (int i : array) {
        if (rand == i) {
            rand = uniqueRandom(min, max, array);
        }
    }
    return rand;
}


Testing::Testing()
{

}

void Testing::runTest (json dict, int type, int difficult)
{
    vector<int> test { createTest(dict, difficult) };
    map<int, bool> results { doTest(dict, test, type) };
    showResults(dict, results);
}

vector<int> Testing::createTest (json dict, int difficult)
{
    vector<int> test { };
    // TODO difficult choosing by user
    int counter { 5 }; // placeholder
    int size { (int)dict.size() };

    if (size >= counter) {
        for (int i = 0; i < counter; ++i) {
            test.push_back(uniqueRandom(0, size, test));
        }
    } else {
        std::cout << "Not enough words in dictionary" << std::endl;
    }
    return test;
}

map<int, bool> Testing::doTest (json dict, vector<int> test, int type)
{
    map<int, bool> results { };

    if (type == WordTranslation) {
        for (int i : test) {
            std::cout << dict[i]["name"] << std::endl;
            string answer { "" };
            std::cin >> answer;
            
            if (answer == dict[i]["translation"]) {
                // TODO increase proportionally
                dict[i]["score"] = (int)dict[i]["score"] + 10;
                results[i] = true;
            } else {
                // TODO decrease proportionally
                dict[i]["score"] = (int)dict[i]["score"] - 10;
                results[i] = false;
            }            
        }
    }
    
    return results;
}

void Testing::showResults (json dict, map<int, bool> results)
{
    
}


Testing::~Testing()
{

}