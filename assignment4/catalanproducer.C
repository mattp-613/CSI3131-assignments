#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int numCatalanNumbers;

//factorial function
long factorial(long value) {
    long result = 1;
    
    for (long i = 1; i <= value; i++) {
        result *= i;  
    }
    
    return result;
}

//calculate Catalan number
long calculateCatalan(int n) {
    long catalan = 0;

    for (int i = 1; i <= n; i++) {
        //get the catalan value
        catalan = factorial(2 * i) / (factorial(i + 1) * factorial(i));
    }

    return catalan;
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        numCatalanNumbers = std::atoi(argv[1]);
    } 
    
    else {
        std::cerr << "Usage: producer <num_of_catalan_numbers>\n";
        return 1;
    }

    //create/open the shared memory segment
    key_t key = ftok("shared_memory_key", 1234);
    int shmId = shmget(key, numCatalanNumbers * sizeof(long), IPC_CREAT | 0666);
    if (shmId == -1) {
        std::cerr << "Failed to create/open shared memory segment.\n";
        return 1;
    }

    //attach to the shared memory segment
    long* sharedMemory = (long*)shmat(shmId, nullptr, 0);
    if (sharedMemory == (void*)-1) {
        std::cerr << "Failed to attach to shared memory segment.\n";
        return 1;
    }

    //generate and write the catalan numbers to shared memory
    for (int i = 0; i < numCatalanNumbers; i++) {
        long catalanNumber = calculateCatalan(i);
        sharedMemory[i] = catalanNumber;
    }

    //detach from the shared memory segment
    if (shmdt(sharedMemory) == -1) {
        std::cerr << "Failed to detach from shared memory segment.\n";
        return 1;
    }

    return 0;
}