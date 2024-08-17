#include "typewise-alert.h"
#include "email_alert.h"
#include "Printonconsole.h"
#include <stdio.h>
#include <string.h>


void sendToEmail(BreachType breachType, void (*sendfunction)(const char* message)) 
{
  const char* recepient = "a.b@c.com";
  const char* breach_message[] = 
  {NULL,
  "Hi, the temperature is too low\n",
  "Hi, the temperature is too high\n" };
  if(breach_message[breachType] != NULL)
  {
    char fullMessage[256];
    snprintf(fullMessage,sizeof(fullMessage),"To%s\n%s", recepient, breach_message[breachType]);
    sendfunction(fullMessage);
  }
}