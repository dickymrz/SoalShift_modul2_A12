#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(){
    char *argv[] = {"pkill", "beta5a", NULL};
    execv("/usr/bin/pkill", argv);
}