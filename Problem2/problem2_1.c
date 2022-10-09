#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    
    int process1 = 0;
    int process2 = 0;
    int p1[2];
    int p2[2];

    pipe(p1);
    pipe(p2);
    process1 = fork();
    if (process1 == 0) {
        //Child1
    }
    else {
        process2= fork();
    }

    if(process1 != 0 && process2 != 0) {
        //Parent
        int num1 = 0;
        printf("Enter a number: ");
        scanf("%d", &num1);
        write(p1[1], &num1, sizeof(int));
        write(p2[1], &num1, sizeof(int));
        wait(NULL);
        int res1 = 0;
        int res2 = 0;
        read(p1[0], &res1, sizeof(int));
        read(p2[0], &res2, sizeof(int));
        printf("The total = <%d>", res1 + res2);
        kill(process1, SIGTERM);
        kill(process2, SIGTERM);
    }
    else if ((process1 == 0 && process2!= 0) || (process1 != 0 && process2 == 0)) {
        //Child1
        wait(NULL);
        int num1 = 0;
        read(p1[0], &num1, sizeof(int));
        int res1 = num1*getpid();
        printf("First Child Input <%d>, Output <%d>\n", num1, res1);
        write(p1[1], &res1, sizeof(int));
        wait(NULL);
    }
    else {
        //Child2
        wait(NULL);
        int num1 = 0;
        read(p2[0], &num1, sizeof(int));
        int res2 = getpid() / num1;
        printf("Second Child Input <%d>, Output <%d>\n", num1, res2);
        write(p2[1], &res2, sizeof(int));
        wait(NULL);
    }
}
