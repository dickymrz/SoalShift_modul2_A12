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


int main() {
    int count=0;
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
    while(1) {

     time_t t2=time(0) ; 
        
        tmp=localtime(&t2);
        strftime(line, sizeof(line), "%d:%m:%Y-%H-%M", tmp);
        struct tm *tmp ; 
        char line[80]; 
        char path[100], t[100];
        if(count%30==0){
            strcpy(t, line);
            strcpy(path,"/home/dennas/log/");
            strcat(path, t);
            strcat(path, "/");
            mkdir(path, 0777);
        }
        int no = count+1;
        char strng[10];
        strcpy(strng, "");
        sprintf(strng, "log%d",no);
        strcat(strng,".log");
        char strngfinal[100];
        strcpy(strngfinal, path);
        strcat(strngfinal,str);

        FILE *fc, *fs;
        int c;
        fc=fopen("/var/log/syslog", "r");
        fs=fopen(strngfinal,"w");
        while(1){
            c=fgetc(fc);
            if(feof(fc)){
                break;
            }
            fputc(c, fs);
        }
        fclose(fc);
        fclose(fs);
        sleep(60);
        count++;
    }
    exit(EXIT_SUCCESS);
}