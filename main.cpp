#include "main.h"


int epollfd;

int sfd;
ThreadPool* pool = new ThreadPool(3);


void HandleSignal(int sig)
{
	delete pool;
	close(sfd);
	std::cout << "server is closed" << std::endl;
    exit(0); 
}

int main()
{
	sfd = ServerInit();
	int epollfd = AddEpollTree(sfd);
	epoll_event events[MAX_EVENTS];
	int nfds;
	signal(SIGINT, HandleSignal);
	while(true)
	{
		nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
		for(int n = 0; n < nfds; ++n)
		{
			if(events[n].data.fd == sfd){
				int cfd = accept(sfd, (struct sockaddr *) NULL, NULL);
				AddEpollTree(cfd);
			}
			else if(events[n].events & EPOLLIN)
			{
				pool->cond.notify_one();
				pool->task_queue.push([=]{	HandleClient(events[n].data.fd);	});
			}	
			else continue;
		}
	}
	return 0;
}
