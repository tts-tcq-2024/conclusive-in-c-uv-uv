#include "typewise-alert.h"
#include "email_alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC)
{
  TemperatureLimits limits[] =
  {
    {0, 35},  // Limit for PASSIVE_COOLING
    {0, 45},  // Limit for HI_ACTIVE_COOLING
    {0, 40}   // Limit for MED_ACTIVE_COOLING
  };
  TemperatureLimits currentLimits = limits[coolingType];
  return inferBreach(temperatureInC, currentLimits.lowerLimit, currentLimits.upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType,sendToConsole);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}


