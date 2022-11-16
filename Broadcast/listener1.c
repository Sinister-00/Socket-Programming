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
    sockfd=socket(AF_INET, SOCK_DGRAM, 0); // create a UDP socket 
    if(sockfd<0){ //check if socket creation was successful
        perror("Error while creating socket");
        exit(1);
    }
    bzero(&saddr, sizeof(saddr)); //clear the server address
    saddr.sin_family=AF_INET; //set the address family to Internet
    saddr.sin_port=htons(1820); //set the port to 1820
    saddr.sin_addr.s_addr=INADDR_ANY;  //set the IP address to any interface
    // Add broadcast membership to socket options
      if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &broadcast, sizeof(broadcast))<0){ //check if socket option was set successfully
        perror("Error while adding socket address");
        exit(1);
    }
    //bind to an ephemeral port
    bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));

    while(1) // Recieves the messages
    {
        bzero(recvline, 100); //clear the buffer
        recvfrom(sockfd, recvline, 100, 0, (struct sockaddr*)&caddr, &caddrsize); //receive the message
        printf("Received %s", recvline); //print the message
    }
}