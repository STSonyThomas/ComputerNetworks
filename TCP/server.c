#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    char* ip ="127.0.0.1";
    int port =5566;
    struct sockaddr_in server_addr, client_addr;
    socklen_t size;
    int server_sock,client_sock;
    int n;
    char buffer[1024];
    //create socket
    server_sock=socket(AF_INET,SOCK_STREAM,0);
    if(server_sock<0){
        perror("[-] Error creating socket");
        exit(1);
    }
    printf("[+] TCP Server socket created");
    // create a memory location for the server_addr details
    //memset should have '\0' and not  "\0" cause one is an integer and other is a character that has to implicitly converted to integer
    memset(&server_addr,'\0',sizeof(server_addr));
    // add server_add details
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=port;
    server_addr.sin_addr.s_addr=inet_addr(ip);

    n= bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(n<0){
        perror("[-] error binding socket\n\n");
        exit(1);
    }
    listen(server_sock,5);
    printf("Listening...\n");

    while(1){
        // for accept the third argument needs to be a pointer to socklen_t instead of socklen_t so the below is done
        size=sizeof(client_addr);
        client_sock = accept(server_sock,(struct sockaddr*)&client_addr,&size);
        printf("[+] Client connected");

        bzero(buffer,1024);
        recv(client_sock,buffer,sizeof(buffer),0);
        printf("Client: %s\n",buffer);

        bzero(buffer,1024);
        strcpy(buffer,"HI, THIS IS SERVER.HAVE A NICE DAY!!!");
        printf("Server: %s\n",buffer);
        send(client_sock,buffer,strlen(buffer),0);

        close(client_sock);
        printf("[+] Client disconnected\n\n");

    }
    return 0;

}