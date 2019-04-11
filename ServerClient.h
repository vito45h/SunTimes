#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H
#include <TimeLib.h>

void setupServerClient(void);
time_t getServerValues();
void printTimeLocal();
int getMinuteCount(void);
#endif
