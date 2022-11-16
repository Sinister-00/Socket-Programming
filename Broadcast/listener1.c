#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include <strings.h>
#include <stdlib.h>
// #include <unistd.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
int main()
{
    char recvline[100]; //buffer to store the received message
    int sockfd; //socket file descriptor
    int broadcast=1; //to set socket option to broadcast
    struct sockaddr_in saddr, caddr; //socket addresses for server and client
    // Set up the server address to bind using socket addressing structure
    socklen_t caddrsize=sizeof(caddr); //size of client socket address
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd<0){
        perror("Error while creating socket");
        exit(1);
    }
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(1820);
    saddr.sin_addr.s_addr=INADDR_ANY; 
    // Add broadcast membership to socket options
      if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &broadcast, sizeof(broadcast))<0){
        perror("Error while adding socket address");
        exit(1);
    }
    //bind to an ephemeral port
    bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));

    while(1) // Recieves the messages
    {
        bzero(recvline, 100);
        recvfrom(sockfd, recvline, 100, 0, (struct sockaddr*)&caddr, &caddrsize);
        printf("Received %s", recvline);
    }
}