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
    doTest(dict, test, type);
}

int createCounter (int size, int difficult) 
{
    int counter { 5 };
    if (difficult == Easy) {
        counter = (int)(size * 0.3);
    }
    if (difficult == Normal) {
        counter = (int)(size * 0.5);
    }
    if (difficult == Hard) {
        counter = (int)(size * 0.8);
    }
    if (difficult == Impossible) {
        counter = size;
    }
    return counter;
}

vector<int> Testing::createTest (json dict, int difficult)
{
    vector<int> test { };
    int size { (int)dict.size() };
    int counter { createCounter(size, difficult) };

    if (size >= counter) {
        for (int i = 0; i < counter; ++i) {
            test.push_back(uniqueRandom(0, size, test));
        }
    } else {
        std::cout << "Not enough words in dictionary" << std::endl;
    }
    return test;
}

string getAnswer ()
{
    return Key::GetString();
}

void Testing::doTest (json dict, vector<int> test, int type)
{
    std::cout << "Test started." << std::endl;
    if (type == WordTranslation) {
        for (int i : test) {
            std::cout << dict[i]["name"] << std::endl;
            proccessAnswer(dict[i], getAnswer(), type);
        }
    }
    if (type == TranslationWord) {
        for (int i : test) {
            std::cout << dict[i]["translation"] << std::endl;
            proccessAnswer(dict[i], getAnswer(), type);
        }
    }
    std::cout << "Test ended." << std::endl;
}

void Testing::proccessAnswer (json word, string answer, int type)
{
    bool result { false };
    string correct { "" };

    if (type == WordTranslation) {
        correct = word["translation"];
        result = answer == correct;
    }
    if (type == TranslationWord) {
        correct = word["name"];
        result = answer == correct;
    }

    if (result) {
        std::cout << "Correct" << std::endl;
    } else {
        std::cout << "Incorrect. Correct word is " << correct << std::endl;
    }
}


Testing::~Testing()
{

}