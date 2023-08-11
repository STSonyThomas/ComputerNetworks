#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>


int main(){
    char* ip ="127.0.0.1";
    int port = 5566;
    struct sockaddr_in server_addr,client_addr;
    socklen_t size;
    int server_sock,client_sock;
    int n;
    char buffer[1024];

    //create a socket
    server_sock=socket(AF_INET,SOCK_STREAM,0);
    if(server_sock<0){
        perror("[-] Error creating socket\n");
        exit(1);
    }
    printf("[+] created a socket for server\n");

    // create memory for the server socket and fill in the details
    memset(&server_addr,'\0',sizeof(server_addr));
    // here we have intitalised memory for server address with size of server address and integer type
    server_addr.sin_family=AF_INET;
    server_addr.sin_port =port;
    server_addr.sin_addr.s_addr=inet_addr(ip);
    //once details are filled in we need to bind the socket to its address details
    n = bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(n<0){
        perror("[-] binding failed\n");
        exit(1);
    }
    printf("socket created at port %d\n",port);
    //here we are setting the server to listen for requests from client
    listen(server_sock, 5);
    printf("Listening...\n");
    while(1){
        size=sizeof(client_addr);
        client_sock= accept(server_sock,(struct sockaddr*)&client_addr,&size);
        printf("[+] client accepts server\n");

        // bzero(buffer,1024);
        // recv(client_sock,buffer,sizeof(buffer),0);
        // printf("Client: %s\n",buffer);

        // bzero(buffer,1024);
        // strcpy(buffer,"HI THIS IS SERVER.HAVE A GRETA DAY!!!\n");
        // send(client_sock,buffer,strlen(buffer),0);
        // printf("Server: %s\n",buffer);
        //palindrome section
        char response[1024];
        recv(client_sock,buffer,sizeof(buffer),0);
        printf("Client: %s\n",buffer);
        strcpy(response,buffer);

        bzero(buffer,1024);
        strcpy(buffer,"True");
        int right = strlen(buffer)-1;
        int left=0;
        
        while(left<right){
            if(response[left]!=response[right]){
                bzero(buffer,1024);
                strcpy(buffer,"False");
            }
            right--;
            left++;
        }
        send(client_sock,buffer,strlen(buffer),0);
        printf("Server: %s\n",buffer);
// palindrome section closes
        close(client_sock);
        printf("[+] connection disconnected");
    }
    return 0;
}