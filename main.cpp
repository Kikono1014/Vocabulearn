#include <iostream>

#include "Dictionary/Dictionary.h"
#include "Controller/Controller.h"
#include "Evaluation/Evaluation.h"
#include "Testing/Testing.h"

Controller ctrl {};

int main ()
{
    Dictionary::TryParseJson();
    while (1) {
        ctrl.processCommand();
    }
    return 0;
}



