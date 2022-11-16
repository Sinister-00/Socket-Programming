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
int main(){
    char recv[100];
    int sockfd;
    int broadcast=1;
    struct sockaddr_in saddr,caddr;
    socklen_t caddrsize=sizeof(caddr);
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd<0)   
    {
        perror("Error while creating socket");
        exit(1);
    }
    bzero(&saddr,sizeof(saddr));
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(1820);
    saddr.sin_addr.s_addr=INADDR_ANY;
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&broadcast,sizeof(broadcast))<0)
    {
        perror("Error while adding socket address");
        exit(1);
    }
    bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
    while(1){
        bzero(recv,100);
        recvfrom(sockfd,recv,100,0,(struct sockaddr*)&caddr,&caddrsize);
        printf("Recieved: %s",recv);
    }
    
    
}