#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    char *ip ="127.0.0.1";
    int port =5566;
    struct sockaddr_in addr;
    int sock;
    char buffer[1024];
    
}