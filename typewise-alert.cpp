#include "typewise-alert.h"
#include "email_alert.h"
#include "Printonconsole.h"
#include "Controller_alert.h"


void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  switch(alertTarget) 
  {
    case TO_CONTROLLER:
      sendToController(breachType,sendToConsole);
      break;
    case TO_EMAIL:
      sendToEmail(breachType,sendToConsole);
      break;
  }
}




