#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int main(int argc, char *argv[]) {
    /* 
     * I have tried it almost for an hour but 
     * I could not write a neat code for this part  
     */

    int process1 = 0; 
    int process2 = 0;
    int process3 = 0;
    int process4 = 0;

    process1 = fork();
    if (process1 == 0) {
        //Child1
    }
    else {
        process2 = fork();
        if(process2 == 0) {
            //Child2
        }
        else {
            process3 = fork();
            if (process3 == 0) {
                //Child
            }
            else {
                process4 = fork();
            }

        }
    }
    
    if (process1 != 0 && process2 != 0 && process3 != 0 && process4 != 0) {
        // Parent Process
        printf("Parent process PID = %d\n", getpid());
        sleep(5);
        kill(process1, SIGTERM);
        printf("Child <%d> killed.", process1);
        kill(process2, SIGTERM);
        printf("Child <%d> killed.", process2);
        kill(process3, SIGTERM);
        printf("Child <%d> killed.", process3);
        kill(process4, SIGTERM);
        printf("Child <%d> killed.", process4);
    }
    else {
        // Child process
        for (int i = 0; i < 7; i++) {
            time_t rawtime;
            struct tm * timeinfo;

            time ( &rawtime );
            timeinfo = localtime ( &rawtime );

            char *str = asctime(timeinfo);
            printf("Child process <%d> ", getpid());
            printf("%s",str);
            sleep(1);
        }
    }

}
