#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

#define W 1
#define R 0

int main(int argc, char **argv) {
    
    char* nameOfProgram = argv[1];
    int   numberOfProcess = atoi(argv[2]);
    char* stringMessage = argv[3];

    //printf("Bastır = %d\n", numberOfProcess);
    
    printf("Parent: Playing Chinese whisper with %d process.\n", numberOfProcess);
    int process = fork(); 
    for (int i = 0; i < numberOfProcess ; i++) {
        if (process > 0) {
            //Parent Process
            wait(NULL);
            process = fork();
        }
        else {
            //child Process
            char *str = "middle";
            char *str2 = malloc(sizeof(char)*50);
            sprintf(str2, "%d", i);
            if (i == 0) {
                str = "first";
            }
            else if (i == numberOfProcess -1 ) {
                str = "last";
            }
            argv[4] = str;
            argv[5] = str2;
            execve(nameOfProgram, argv++, NULL);
            
            free(str2);
        }
    }
    
    if (process>0) {
        wait(NULL);
        printf("Parent terminating...\n");
    }
}
