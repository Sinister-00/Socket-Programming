#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main()
{
    char recvline[100];
    int sockfd;
    int broadcast=1;
    //initialising socket address and its length
    struct sockaddr_in saddr, caddr;
    socklen_t caddrsize=sizeof(caddr);
    // creating a socket 
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);
    //before assigning the socket id and port number assign its value to zero
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(22000);
    saddr.sin_addr.s_addr=INADDR_ANY;
    //binding the socket
    bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
y
    while(1)
    {
        //clearing the recievers output
        bzero(recvline, 100);
        recvfrom(sockfd, recvline, 100, 0, (struct sockaddr*)&caddr, &caddrsize); //recieving the message from sender
        printf("Received %s", recvline);// printing recieved message
    }
}