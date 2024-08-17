#ifndef EMAIL_ALERT_H
#define EMAIL_ALERT_H

void sendToConsole(const char* message);
void sendToEmail(BreachType breachType, void (*sendFunction)(const char* message));


#endif 