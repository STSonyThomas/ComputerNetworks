#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
//some other header files
//sys/socket.h contains the functions socket connect send rcv and
#include<sys/socket.h>
// these headers contain the data structures that make the functions in sys/socket.h work
#include<netinet/in.h>
#include<netdb.h>
// SMTP is basically a glorified way of sending mails with the commands HELO(Identifying the client to the srver)
// MAIL sends the senders address
// RCPT send the recievers address
// DATA sends the data of the mail
// if you have these command recognitions in the server when sent by the reciever then you have a complete mail in SMTP
//usually port 25 is used for smtp. I am gonna use 5566 cause I wanna see what happens if I dont.


int main(){
    char *ip ="127.0.0.1";
    int port= 25;
    int client,server;
    struct sockaddr_in server_addr,client_addr;
    socklen_t size;
    int n;
    char buffer[1024];

    // first create a socket for the server since this is the server
    server=socket(AF_INET,SOCK_STREAM,0);
    if(server<0){
        perror("[-] Error creating server socket\n");
        exit(1);
    }
    printf("[+] created TCP socket for SMTP\n");

    // next create the memory for the address structure of server(sockaddr_in oru structure aan)
    memset(&server_addr,'\0',sizeof(server_addr));
    //fill in the details of the server
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=port;
    server_addr.sin_addr.s_addr=inet_addr(ip);
    // bind server socket to the server address space
    n= bind(server,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(n<0){
        perror("[-] Error binding\n");
        exit(1);
    }
    //binding complete
    //enable listening
    listen(server,5);
    printf("Listening...\n");
    size=sizeof(client_addr);
    client=accept(server,(struct sockaddr*)&client_addr,&size);
    printf("[+] Client has accepted server\n");
    // from here onwards we can send and receive data
    bzero(buffer,1024);
    //first HELO to identify client for server
    // char HELO[]="HELO\n\t";
    send(client,"HELO",strlen("HELO"),0);
    n=recv(client,buffer,sizeof(buffer),0);
    // buffer[n]='\0';
    printf("Client: %s\n",buffer);

    while(1){
 
        // this is to clear the memory space alloted to buffer of any previous data
        bzero(buffer,1024);
        recv(client,buffer,sizeof(buffer),0);
        printf("Client: %s\n",buffer);
        (client,buffer,sizeof(buffer),0);
        if(strstr(buffer,"QUIT")!=NULL){
            send(client,"221 BYE\r\n",strlen("221 BYE\r\n"),0);
        }else{
            char *response ="220 OK\r\n";
            send(client,response,strlen(response),0);
        }
    }
    close(client);
    close(server);
    return 0;
}