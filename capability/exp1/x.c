// OS: Ubuntu 22.04.1 64bit Desktop.
#include <stdio.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <string.h> 
#include <unistd.h> 
#include <limits.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    printf("try to open tcp/udp socket with port lower than 1024\n");
    int port = atoi(argv[1]);
    struct sockaddr_in serv_addr; 
    int ret = socket(AF_INET, SOCK_STREAM, 0);
    int sock_fd = ret;
    printf("socket fd: %d\n", ret);

    // setup sockaddr_in
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons( port );     // lower than 1024 require priv.

    ret = bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    printf("bind: %d\n", ret);
    if(bind==-1) return -1;

/*
    // this works if bind is successful.

    ret = listen(sock_fd, 10);
    printf("listen: %d\n", ret);

    printf("start accepting...\n");
    ret = accept(sock_fd, (struct sockaddr*)NULL, NULL); 
    printf("accept: %d\n", ret);
*/
    return 0;
} 

