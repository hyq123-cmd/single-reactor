#ifndef _MAIN_H_
#define _MAIN_H_

#include <arpa/inet.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <signal.h>
#include <condition_variable>
#include <functional>
#include <queue>
#include <vector>
#include <chrono>

#include "reactor.h"
#include "threadpool.h"

#define server_ip_address "192.168.52.130"
#define server_port 8888
#define MAX_EVENTS 10 

extern int epollfd;

#endif
