#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

long factorial(int value) {
    long result = 1;
    
    for (int i = 1; i <= value; i++) {
        result *= i;

    }
    return result;
}

long calculateCatalan(int n) {
    long catalan = 0;

    for (int i = 0; i <= n; i++) {
        catalan = factorial(2 * i) / ((factorial(i + 1) * factorial(i)));
    }

    return catalan;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <num_catalan_numbers>\n", argv[0]);
        return 1;
    }

    int numCatalanNumbers = atoi(argv[1]);
    const int SHARED_MEMORY_SIZE = sizeof(long) * numCatalanNumbers;

    //create a shared memory object
    int shm_fd = shm_open("/catalan_numbers", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    //set the shared memory object size
    if (ftruncate(shm_fd, SHARED_MEMORY_SIZE) == -1) {
        perror("ftruncate");
        return 1;
    }

    //map the shared memory object into the process's address space
    long *sharedMemory = (long *)mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (sharedMemory == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    //generate and write Catalan numbers to shared memory
    for (int i = 1; i < numCatalanNumbers + 1; i++) {
        printf("%ld\n", calculateCatalan(i));
        sharedMemory[i] = calculateCatalan(i);
    }

    //clean up and close shared memory
    munmap(sharedMemory, SHARED_MEMORY_SIZE);
    close(shm_fd);

    return 0;
}