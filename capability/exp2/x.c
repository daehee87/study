// OS: Ubuntu 22.04.1 64bit Desktop.
#include <stdio.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <string.h> 
#include <unistd.h> 

int main(int argc, char* argv[]){
    int fd = open(argv[1], O_RDONLY);
    printf("open: %d\n", fd);
    return 0;
} 

