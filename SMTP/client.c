#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
//extras
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

int main(){
    char *ip="127.0.0.1";
    int port =25;
    struct sockaddr_in addr;
    socklen_t size;
    int server;
    int n;
    char buffer[1024];

    //create a socket for the server
    server=socket(AF_INET,SOCK_STREAM,0);
    if (server<0){
        perror("[-] error creating server socket\n");
        exit(1);
    }
    printf("[+] created server socket");
    //creating memory for the server address
    memset(&addr,'\0',sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=port;
    addr.sin_addr.s_addr=inet_addr(ip);

    //binding the socket
    n=connect(server,(struct sockaddr*)&addr,sizeof(addr));
    if(n<0){
        perror("[-] Error binding\n");
        exit(1);
    }
    printf("[+] Successfully connected to the server\n");
    bzero(buffer,1024);
    n=recv(server,buffer,sizeof(buffer),0);
    buffer[n]='\0';
    
    if(strcmp(buffer,"HELO")==0){
        printf("Server: %s\n",buffer);
        char HELO[]="HELO localhost\r\n";
        send(server,HELO,strlen(HELO),0);
    }
    char *emailCommands[] ={
        "HELO localhost\r\n",
        "MAIL FROM: <sender@example.com>\r\n",
        "RCPT TO: <receiver@example.com>\r\n",
        "DATA\r\n",
        "Subject: Test Email\r\n",
        "This is a test email sent using SMTP client in C.\r\n",
        ".\r\n",
        "QUIT\r\n"
    };
    for (int i = 0; i < sizeof(emailCommands) / sizeof(emailCommands[0]); i++) {
        send(server, emailCommands[i], strlen(emailCommands[i]), 0);
        recv(server, buffer, sizeof(buffer), 0);
        printf("Server: %s", buffer);
    }
    close(server);
    
    return 0;
}