#ifndef MOCK_FUNCTIONS_H
#define MOCK_FUNCTIONS_H

#include "gmock/gmock.h"

class MockFunctions 
{
public:
    MOCK_METHOD(void, SendToConsole, (const char* message));
};

#endif