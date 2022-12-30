// OS: Ubuntu 22.04.1 64bit Desktop.
#include <stdio.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <string.h> 
#include <unistd.h> 
#include <limits.h>

int _getcwd() {
   char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }
   return 0;
}

int main(){
    _getcwd();

    // get an fd outside chroot. before we jail this process.
    int hole = open("/etc/passwd", O_RDONLY);

    int ret;
    if((ret = chroot("jail"))<0) { 
        fprintf(stderr, "Failed to chroot to error:%s\n",strerror(errno)); 
        exit(1); 
    }
    ret = chdir("/");   // this is normal. try change this with .. or various stuffs
    printf("chdir ret: %d, %s\n", ret, strerror(errno));
    _getcwd();

    printf("are we in jail?\n");
    int fd = open("/etc/passwd", O_RDONLY);
    char buf[32] = "yes. we are locked.\n\x00";
    read(fd, buf, 32);
    write(1, buf, 32);

    // see if this works.
    printf("can we access hole?\n");
    char buf2[32] = "access denied.\n\x00";
    read(hole, buf2, 32);
    write(1, buf2, 32);
} 

