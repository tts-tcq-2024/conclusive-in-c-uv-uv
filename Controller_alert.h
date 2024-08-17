#ifndef CONTROLLER_ALERT_H
#define CONTROLLER_ALERT_H

void sendToController(BreachType breachType, void (*sendFunction)(const char* message));


#endif 