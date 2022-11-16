#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#include <strings.h>
#include <stdlib.h>

#include <sys/ioctl.h>

#include <netinet/in.h>

#include <netdb.h>

int main()
{
    char sendline[100];
    int sockfd;
    int broadcast=1;
    struct sockaddr_in saddr;
    //creating a socket and handling the failure
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd<0){
        perror("Error while creating socket.");
        exit(1);
    }

    bzero(&saddr, sizeof(saddr)); //assigning sender address
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(1820); //assigning port number
    saddr.sin_addr.s_addr=inet_addr("172.20.10.15");//ip address
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));//setting socket options for the broadcast
    bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
    int rc;
//sending message from sender by using infinite loop
    while(1)
    {
        bzero(sendline, 100);
        fgets(sendline, 100, stdin);//getting input from stdin
        rc=sendto(sockfd, sendline, 100, 0, (struct sockaddr*)&saddr, sizeof(saddr));
        if (rc < 0) {  //wnenever we have error while sending
            perror("Error while sending");
            exit(1);
        } 
    }
}