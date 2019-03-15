#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h> 
#include <grp.h> 

int main() {
  pid_t pid, sid;
  pid = fork();
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }
  umask(0);
  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  
  while(1) 
  {
   char dir[] = "/home/insane/hatiku/elen.ku";
   struct stat info;  
   stat(dir, &info);

        char mode[] = "0777"; 
        int a;
        a = strtol(mode, 0, 8);
        chmod(dir, a);
        
        struct passwd *pw;
        struct group  *gr;
        pw = getpwuid(info.st_uid); 
        gr = getgrgid(info.st_gid);
    
    if(strcmp(gr->gr_name,"www-data")==0 && strcmp(pw->pw_name, "www-data")==0)
    { 
        remove("/home/insane/hatiku/elen.ku");
    }
    sleep(3);
  } exit(EXIT_SUCCESS);
}