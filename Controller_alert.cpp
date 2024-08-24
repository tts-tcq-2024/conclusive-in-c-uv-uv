#include "typewise-alert.h"
#include "Controller_alert.h"
#include "Printonconsole.h"
#include <stdio.h>
#include <string.h>

void sendToController(BreachType breachType, SendFunction sendFunction) 
{
  if (breachType != NORMAL) 
  {
  const unsigned short header = 0xfeed;
  char messagetocontroller[256];
  snprintf(messagetocontroller, sizeof(messagetocontroller),"%x : %x\n", header, breachType);
  sendFunction(messagetocontroller);
  }
}