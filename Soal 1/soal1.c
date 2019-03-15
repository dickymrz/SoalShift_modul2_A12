#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

int main() {
  pid_t pid, sid;
  pid = fork();
  if (pid < 0) {
    exit(EXIT_FAILURE); }
  if (pid > 0) {
    exit(EXIT_SUCCESS); }
  umask(0);
  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE); }
  if ((chdir(".")) < 0) {
    exit(EXIT_FAILURE); }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

while(1){
        struct dirent *filex; 
        DIR *dir = opendir("/home/insane/");
        char* ptrsub;
        char f1[100];
        char f2[100];
        char loc[100];
                if (dir != NULL){
                        while((filex = readdir(dir)) != NULL) {
                                strcpy(f1, filex->d_name);
                                ptrsub = strstr(f1, ".png");
                if(ptrsub != NULL){
                        strncpy(f2, filex->d_name, strlen(filex->d_name) - 4);
                        strcat(f2, "_grey.png");
                        strcpy(loc,"/home/insane/modul2/gambar/");
                        strcat(loc, f2);
                        rename(f1 , loc);
                                }
                                                                }
                                }
        sleep(30);
        }
        exit(EXIT_SUCCESS);
}
