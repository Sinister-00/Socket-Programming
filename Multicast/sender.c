#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    // Using multicast to send message to two server
    int n=1; //number of servers
    int sockfd;  //socket file descriptor
    char sendline[100];   //buffer to store the message  
    char *recipient_ip[n]; //array to store the ip address of the servers
    recipient_ip[0]="172.20.10.4";//initialising reciepent ip address
    // recipient_ip[1]="192.168.122.142";
    //creating socket
    sockfd=socket(AF_INET, SOCK_DGRAM, 0); // create a UDP socket

    
    while(1) // infinte loop
    {
        bzero(sendline, sizeof(sendline)); //setting input value to zero in every iteration
        fgets(sendline, 100, stdin);// read the input from i/o
        //looping through number of recievers
        for(int i=0; i<n; i++)
        {
            // Assigning the socket address
            struct sockaddr_in saddr; //socket addresses for server and client

            bzero(&saddr, sizeof(saddr)); //assigning sender address
            saddr.sin_family=AF_INET; //set the address family to Internet
            saddr.sin_port=htons(22000); //assigning port number
            saddr.sin_addr.s_addr=inet_addr(recipient_ip[i]); //ip address of the receiver
            //binding the socket
            bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
            //sending the socket to reciever
            sendto(sockfd, sendline, 100, 0, (struct sockaddr*)&saddr, sizeof(saddr));
            
        }
    }
}

