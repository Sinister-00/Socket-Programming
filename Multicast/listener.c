#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main()
{
    char recvline[100]; //buffer to store the received message
    int sockfd; //socket file descriptor
    int broadcast=1; //to set socket option to broadcast
    //initialising socket address and its length
    struct sockaddr_in saddr, caddr;
    socklen_t caddrsize=sizeof(caddr); //size of client socket address
    // creating a socket 
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);
    //before assigning the socket id and port number assign its value to zero
    bzero(&saddr, sizeof(saddr)); //clear the server address
    saddr.sin_family=AF_INET; //set the address family to Internet
    saddr.sin_port=htons(22000); //set the port to 22000
    saddr.sin_addr.s_addr=INADDR_ANY; //set the IP address to any interface
    //binding the socket
    bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr)); //bind to an ephemeral port

    while(1) //recieves the message 
    {
        //clearing the recievers output
        bzero(recvline, 100);
        recvfrom(sockfd, recvline, 100, 0, (struct sockaddr*)&caddr, &caddrsize); //recieving the message from sender
        printf("Received %s", recvline);// printing recieved message
    }
}