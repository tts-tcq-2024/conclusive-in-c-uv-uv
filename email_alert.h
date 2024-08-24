#ifndef EMAIL_ALERT_H
#define EMAIL_ALERT_H

typedef void (*SendFunction)(const char* message);
void sendToEmail(BreachType breachType, SendFunction sendFunction);


#endif 