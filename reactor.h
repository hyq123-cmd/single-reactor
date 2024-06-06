#ifndef _REACTOR_H_
#define _REACTOR_H_

#include "main.h"

int ServerInit(void);
int AddEpollTree(int);
void HandleClient(int);

#endif