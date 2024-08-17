#ifndef CONTROLLER_ALERT_H
#define CONTROLLER_ALERT_H

typedef void (*SendFunction)(const char* message);
void sendToController(BreachType breachType, SendFunction sendFunction);


#endif 