#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/sysmacros.h>
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
  int ctr=1;
  while(1) {
    //Daemon program start
   char makanEnak[]="/home/dennas/makanan/makanenak.txt";
   struct stat info;  //mengecek file apakah dibuka atau tidak
   stat(makanEnak,&info);//sama seperti di atas.
   time_t now;//untuk perbandingan waktu
   time(&now);//waktu jam computer
   int beda;

   beda = difftime(now, info.st_atime); 
   if(beda<=30){ //jika waktu dibawah 3 detik
     printf("atime :  %d  ",beda); //Waktunya beda berapa detik
     char path[200],str[50];
     strcpy(path, "/home/dennas/makanan/makan_sehat");
     sprintf(str,"%d.txt",ctr);
     strcat(path,str);
     char *argv[] = {"touch", path, NULL};
     execv("/usr/bin/touch", argv);
     ctr++;
     sleep(5);
     }

  }
  exit(EXIT_SUCCESS);
}