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
    std::string brandName;
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
class CheckAndAlertTest : public ::testing::TestWithParam<TestCase> {
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
        BatteryCharacter batterychar;
        batterychar.coolingType = testcase.coolingType;
        strncpy(batterychar.brand, testcase.brandName.c_str(), sizeof(batterychar.brand));
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
    TestFunction(testCase);
}
INSTANTIATE_TEST_SUITE_P(
    AllCases,  
    CheckAndAlertTest,
    ::testing::Values(
        TestCase{"PassiveCoolingTooLowCorrectMessageToController", PASSIVE_COOLING, "BrandA", -1, TO_CONTROLLER, "feed : 1\n", mocksendToConsole},
        TestCase{"PassiveCoolingTooHighCorrectMessageToController", PASSIVE_COOLING, "BrandA", 38, TO_CONTROLLER, "feed : 2\n", mocksendToConsole},
        TestCase{"Hi-ActiveCoolingTooHighCorrectMessageToController", HI_ACTIVE_COOLING, "BrandA", 50, TO_CONTROLLER, "feed : 2\n", mocksendToConsole},
        TestCase{"Hi-ActiveCoolingTooLowCorrectMessageToController", HI_ACTIVE_COOLING, "BrandA", -1, TO_CONTROLLER, "feed : 1\n", mocksendToConsole},
        TestCase{"MED-ActiveCoolingTooLowCorrectMessageToController", MED_ACTIVE_COOLING, "BrandA", -5, TO_CONTROLLER, "feed : 1\n", mocksendToConsole},
        TestCase{"MED-ActiveCoolingTooHighCorrectMessageToController", MED_ACTIVE_COOLING, "BrandA", 44, TO_CONTROLLER, "feed : 2\n", mocksendToConsole},
        TestCase{"MED-ActiveCoolingNormalNoMessageToController", MED_ACTIVE_COOLING, "BrandA", 36, TO_CONTROLLER, nullptr, sendToConsole},
        TestCase{"Hi-ActiveCoolingNormalNoMessageToController", HI_ACTIVE_COOLING, "BrandA", 44, TO_CONTROLLER, nullptr, sendToConsole},
        TestCase{"PassiveCoolingNormalNoMessageToController", PASSIVE_COOLING, "BrandA", 44, TO_CONTROLLER, nullptr, sendToConsole},
        TestCase{"PassiveCoolingTooLowCorrectMessageToMail", PASSIVE_COOLING, "BrandB", -1, TO_EMAIL, "Toa.b@c.com\nHi, the temperature is too low\n", mocksendToConsole},
        TestCase{"PassiveCoolingTooHighCorrectMessageToMail", PASSIVE_COOLING, "BrandB", 38, TO_EMAIL, "Toa.b@c.com\nHi, the temperature is too high\n", mocksendToConsole},
        TestCase{"Hi-ActiveTooHighCorrectMessageToMail", HI_ACTIVE_COOLING, "BrandB", 50, TO_EMAIL, "Toa.b@c.com\nHi, the temperature is too high\n", mocksendToConsole},
        TestCase{"Hi-ActiveTooLowCorrectMessageToMail", HI_ACTIVE_COOLING, "BrandB", -1, TO_EMAIL, "Toa.b@c.com\nHi, the temperature is too low\n", mocksendToConsole},
        TestCase{"MED-ActiveTooLowCorrectMessageToMail", MED_ACTIVE_COOLING, "BrandB", -5, TO_EMAIL, "Toa.b@c.com\nHi, the temperature is too low\n", mocksendToConsole},
        TestCase{"MED-ActiveTooHighCorrectMessageToMail", MED_ACTIVE_COOLING, "BrandB", 44, TO_EMAIL, "Toa.b@c.com\nHi, the temperature is too high\n", mocksendToConsole}
    )
);
