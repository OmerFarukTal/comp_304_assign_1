#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>


int main(int argc, char **argv) {
    const int SIZE = 4096;
    const char* name = "OS";
    int shm_fd;
    void* ptr;

    if (strcmp(argv[4], "first") == 0) {
        //Open shared memory
        shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
        ftruncate(shm_fd, SIZE);
        ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        
        //Write the mesaj
        sprintf(ptr, "%s", argv[3]);
        printf("Child %d: %s\n", atoi(argv[5]), (char*) ptr); 
    }
    else if (strcmp(argv[4], "last") == 0) {
        //Acces to share memory
        shm_fd = shm_open(name, O_RDWR, 0666);
        ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

        //Change the message
        char* message = strdup((char*) ptr);

        int ind1 = (rand()*getpid())%strlen(message);
        int ind2 = (rand()*getpid())%strlen(message);
        
        char temp = message[ind1];
        message[ind1] = message[ind2];
        message[ind2] = temp;

        //Write the mesaj
        sprintf(ptr, "%s", message);
        shm_unlink(name);
        printf("Child %d: %s\n", atoi(argv[5]), message); 
    }
    else {
        //Acces to share memory
        shm_fd = shm_open(name, O_RDWR, 0666);
        ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

        //Change the message
        char* message = strdup((char*) ptr);

        int ind1 = (rand()*getpid())%strlen(message);
        int ind2 = (rand()*getpid())%strlen(message);
        
        char temp = message[ind1];
        message[ind1] = message[ind2];
        message[ind2] = temp;
        

        //Write the mesaj
        sprintf(ptr, "%s", message);
        printf("Child %d: %s\n", atoi(argv[5]), message); 
    }
}


