#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

int main(int argc, char **argv) {
    int process = fork();
    /*
     * It returns 0 to the child process.
     * It return PID of child to parent process.
     */

    if (process == 0) {
        //Child process
        for (int i = 0; i < 7; i++) {
            time_t rawtime;
            struct tm *timeinfo;
            
            time(&rawtime);
            timeinfo = localtime(&rawtime);

            char *str = asctime(timeinfo);
            printf("Child process <%d>", getpid());
            printf("%s", str);
            sleep(1);
        }
    }
    else {
        //Child process
        printf("Parent process. PID =%d\n", getpid());
        sleep(5);
        kill(process, SIGTERM);
        printf("Child <%d> killed.", process);
    }
}
