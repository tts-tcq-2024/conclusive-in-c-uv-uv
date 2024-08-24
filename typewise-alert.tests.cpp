#include <gtest/gtest.h>
#include "typewise-alert.h"
#include "gmock/gmock.h"
#include "Controller_alert.h"
#include "email_alert.h"
#include "mock_functions.h"
#include "Printonconsole.h"
#include "temperature_alert.h"
struct TestCase {
    std::string title;
    CoolingType coolingType;
    const char* brandName;
    double temperatureInC;
    AlertTarget alertTarget;
    const char* expectedMessage;
    void (*sendToConsoleFunc)(const char*);
};
MockFunctions* mockFunctions;
void mocksendToConsole(const char* message) 
{
    mockFunctions->sendToConsole(message);
}
class CheckAndAlertTest : public ::testing::Test {
protected:
    void SetUp() override 
    {
        mockFunctions = new MockFunctions();
    }

    void TearDown() override 
    {
        delete mockFunctions;
    }

    void TestFunction(const TestCase& testcase)
    {
        std::cout << "Running the test case:" << testcase.title << std::endl;
        BatteryCharacter batterychar = {testcase.coolingType,testcase.brandName};
        if (testcase.expectedMessage != nullptr)
        {
            EXPECT_CALL(*mockFunctions, sendToConsole(::testing::StrEq(testcase.expectedMessage))).Times(1);
        }
        else
        {
            EXPECT_CALL(*mockFunctions, sendToConsole(::testing::_)).Times(0);
        }
        checkAndAlert(testcase.alertTarget,batterychar,testcase.temperatureInC,testcase.sendToConsoleFunc);
    }
};

TEST_P(CheckAndAlertTest, CheckAndAlertParameterized) 
{
    TestCase testCase = GetParam();
    CommonTestFunction(testCase);
}
INSTANTIATE_TEST_SUITE_P(
    AllCases,
    CheckAndAlertTest,
    ::testing::Values(
        TestCase{"PassiveCoolingTooLowCorrectMessageToController","BrandA", PASSIVE_COOLING, -1, TO_CONTROLLER, "feed : 1\n", mocksendToConsole}
    )
);
