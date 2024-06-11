#include "reactor.h"

int ServerInit()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)    std::cerr << "error in server initialization" << std::endl; 
    
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip_address, &addr.sin_addr.s_addr);

    bind(fd, (sockaddr*)&addr, sizeof(addr));
    listen(fd, 128);

    return fd;
}

int AddEpollTree(int fd)
{
    static bool flag = true;
    static epoll_event ev;
    if(flag)
    {
        epollfd = epoll_create(1);
        if(epollfd == -1)
        {
            std::cerr << "error in creating epoll" << std::endl; 
            return -1;
        }
    } 

    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = fd;

    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    if(!flag)   std::cout << "add a new client suessfully!" << std::endl;
    flag = false;
    
    return epollfd;
}

void HandleClient(int cfd)
{
    char buf[512];
    memset(buf, 0, sizeof(buf));
    int len = read(cfd, buf, sizeof(buf));
    if(len > 0){
        printf("receive from client-%d is : %s\n", cfd, buf);
        fflush(stdout);
        //std::this_thread::sleep_for(std::chrono::seconds(10));
        if(!strcmp(buf, "close")){
            epoll_ctl(epollfd, EPOLL_CTL_DEL, cfd, NULL);
            close(cfd);
	    }
        else write(cfd, buf, strlen(buf));
    }
}
