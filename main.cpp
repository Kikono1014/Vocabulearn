#include <iostream>

#include "Dictionary/Dictionary.h"
#include "Controller/Controller.h"
#include "Evaluation/Evaluation.h"
#include "Testing/Testing.h"

Controller ctrl {};

int main ()
{
    Dictionary::TryParseJson(); // try open dictionary and parse it. Make base file if get error
    while (1) {
        ctrl.processCommand();
    }
    return 0;
}



