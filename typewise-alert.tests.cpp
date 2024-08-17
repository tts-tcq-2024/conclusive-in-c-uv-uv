#include <gtest/gtest.h>
#include "typewise-alert.h"
#include "gmock/gmock.h"
#include "Controller_alert.h"
#include "email_alert.h"
#include "mock_functions.h"
#include "Printonconsole.h"
#include "temperature_alert.h"

MockFunctions* mockFunctions;

void mocksendToConsole(const char* message) 
{
    mockFunctions->sendToConsole(message);
}
class CheckAndAlertTest : public ::testing::Test {
protected:
    void SetUp() override {
        mockFunctions = new MockFunctions();
    }

    void TearDown() override {
        delete mockFunctions;
    }
};

TEST_F(CheckAndAlertTest, PassiveCoolingTooLowCorrectMessageToController)
{
    BatteryCharacter batterychar = {PASSIVE_COOLING,"BrandA"};
    double temperatureInC = -1;
    EXPECT_CALL(*mockFunctions, sendToConsole("feed : 1\n")).Times(1);
    checkAndAlert(TO_CONTROLLER, batterychar, temperatureInC);
}
