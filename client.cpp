#include <signal.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int sfd;
std::string server_ip_address = "192.168.52.130";
int server_port = 8888;

int ClientInit(sockaddr_in& addr)
{
    //create a socket description
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    //get ip type
    addr.sin_family = AF_INET;
    //get host port
    addr.sin_port = htons(server_port);
    //get ip iddress
    inet_pton(AF_INET, server_ip_address.c_str(),  &addr.sin_addr.s_addr);

    return fd;
}

void HandleSignal(int sig)
{
    printf("\nreceive signal of %d, and client will be disconnectted!\n", sig);
    fflush(stdout);
    write(sfd, "close", 5);
    close(sfd);
    exit(0); 
}

int main()
{
    //sfd: server file description, saddr: server address
    sockaddr_in saddr;
    sfd = ClientInit(saddr);
    int ret;
    signal(SIGINT, HandleSignal);
    do{
        ret = connect(sfd, (struct sockaddr*)&saddr, sizeof(saddr));
        std::cout << "try to connect server...\n";
        sleep(1);
    }while(ret == -1);

    std::cout << "connect server successfully!\n";

    while(1)
    {
        static char buf[1024] = {0};
        static std::string send_str;
        std::cout << "please enter a string: ";
        getline(std::cin, send_str); 
        write(sfd, send_str.c_str(), send_str.size());
        // int len  = read(sfd, buf, sizeof(buf));
        // if(len > 0){
        //     std::cout << "client receive is: " << buf << std::endl;
        //     memset(buf, 0 , sizeof(buf));
        // } 
        // else if(len == 0)
        // {
        //     std::cerr << "lose connection with server.\n";
        //     break;
        // }

    }

    return 0;
}
