#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
    char *ip="127.0.0.1";
    int port =5566;
    struct sockaddr_in addr;
    socklen_t size;
    char buffer[1024];
    int sock;

    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0){
        perror("[-] error creating socket\n");
        exit(1);
    }
    printf("[+] created TCP socket\n");
    //created a socket

    memset(&addr,'\0',sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=port;
    addr.sin_addr.s_addr=inet_addr(ip);

    connect(sock,(struct sockaddr*)&addr,sizeof(addr));

    // bzero(buffer,1024);
    // strcpy(buffer,"THIS IS CLIENT WAITING FOR RESPONSE FROM SERVER\n");
    // send(sock,buffer,strlen(buffer),0);
    // printf("Client: %s\n",buffer);

    // bzero(buffer,1024);
    // recv(sock,buffer,sizeof(buffer),0);
    // printf("Server: %s\n",buffer);
    bzero(buffer,1024);
    printf("Enter a word for palindrome checking;");
    fgets(buffer,1024,stdin);
    send(sock,buffer,strlen(buffer),0);
    printf("Client: %s\n",buffer);

    bzero(buffer,1024);
    recv(sock,buffer,sizeof(buffer),0);
    printf("Server: %s\n",buffer);

    close(sock);
    printf("[+] socket closed and connections terminated\n\n");

    return 0;

    
}