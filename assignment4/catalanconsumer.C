#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const int MAX_CATALAN_NUMBERS = 100;

    //open the shared memory object
    int shm_fd = shm_open("/catalan_numbers", O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    //nap the shared memory object into the process's address space
    long *sharedMemory = (long *)mmap(NULL, sizeof(long) * MAX_CATALAN_NUMBERS, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (sharedMemory == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    //read and output the catalan numbers from shared memory
    int i = 0;
    while (sharedMemory[i] != 0) {
        printf("%ld ", sharedMemory[i]); //print numbers
        i++;
    }
    printf("\n");

    //clean up and close shared memory (garbage clean)
    munmap(sharedMemory, sizeof(long) * MAX_CATALAN_NUMBERS);
    close(shm_fd);

    //unlink the shared memory object (garbage clean)
    if (shm_unlink("/catalan_numbers") == -1) {
        perror("shm_unlink");
        return 1;
    }

    return 0;
}