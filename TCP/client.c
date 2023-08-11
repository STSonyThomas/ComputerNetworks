#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
    char *ip ="127.0.0.1";
    int port =5566;
    struct sockaddr_in sock_addr;
    socklen_t size;
    char buffer[1024];
    int sock;

    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock<0){
        perror("[-] Error creating socket\n");
        exit(1);
    }
    printf("[+] TCP socket created\n");
    memset(&sock_addr,'\0',sizeof(sock_addr));
    sock_addr.sin_family =AF_INET;
    sock_addr.sin_port =port;
    sock_addr.sin_addr.s_addr =inet_addr(ip);
    //connect socket to socket details
    connect(sock,(struct sockaddr*)&sock_addr,sizeof(sock_addr));

    bzero(buffer,1024);
    strcpy(buffer,"HI, THIS IS CLIENT.WAITING FOR RESPONSE!!!");
    printf("Client : %s\n",buffer);
    send(sock,buffer,strlen(buffer),0);

    bzero(buffer,1024);
    recv(sock,buffer,sizeof(buffer),0);
    printf("Server: %s\n",buffer)
    ;
    close(sock);
    printf("[+] Disconnected from the server");
    return 0;


}