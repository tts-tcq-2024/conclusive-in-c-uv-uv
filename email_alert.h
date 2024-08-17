#ifndef EMAIL_ALERT_H
#define EMAIL_ALERT_H

void sendToEmail(BreachType breachType, void (*sendFunction)(const char* message));
void sendToConsole(const char* message);

#endif 