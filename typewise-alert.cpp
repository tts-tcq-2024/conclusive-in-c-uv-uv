#include "typewise-alert.h"
#include "email_alert.h"
#include "Printonconsole.h"
#include "Controller_alert.h"


void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC, void (*sendToConsoleFunc)(const char* message)) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  switch(alertTarget) 
  {
    case TO_CONTROLLER:
      sendToController(breachType,sendToConsoleFunc);
      break;
    case TO_EMAIL:
      sendToEmail(breachType,sendToConsoleFunc);
      break;
  }
}




