#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
    char *ip ="127.0.0.1";
    int port = 5566;
    struct sockaddr_in server_addr,client_addr;
    int server_sock;
    socklen_t size;
    char buffer[1024];
    int n;

    //creating the socket for server
    server_sock=socket(AF_INET,SOCK_DGRAM,0);
    if(server_sock<0){
        perror("[-] error creating a socket\n");
        exit(1);
    }
    printf("[+] created a socket for UDP");
    //create the memory for server address
    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    //binding the socket to the address
    if(bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        perror("[-] error binding the socket to address\n");
        exit(1);
    }
    printf("[+] connection created\n");

    //listening
    printf("Server is listening...\n");

    while(1){
        int count = 0;
        int total=0;
        while(count<4){
            bzero(buffer,1024);
            size= sizeof(client_addr);
            recvfrom(server_sock,buffer,sizeof(buffer),0,(struct sockaddr*)&client_addr,&size);
            total+=(int)buffer;
            count++;
            printf("Client: %s\n",buffer);
        }
        int percent =(int)count/4;
        bzero(buffer,1024);
        if(percent>50 && percent<100){
            strcpy(buffer,"Pass");
        }
        else if(percent>90 && percent<50){
            strcpy(buffer,"Fail");
        }
        sendto(server_sock,buffer,strlen(buffer),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
        printf("Server: %s\n",buffer);

        
    }
    close(server_sock);
    return 0;

}