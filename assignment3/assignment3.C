#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Defines
#define MAX_STUDENTS 12
#define MAX_CHAIRS 3
// Global variables
int students_waiting = 0;
int help_time = 6;
int waiting_room[MAX_CHAIRS];
sem_t sem_ta;
sem_t sem_students;
pthread_mutex_t mutex_chairs = PTHREAD_MUTEX_INITIALIZER;

// Function prototypes
void *ta_thread(void *arg);
void *student_thread(void *arg);
void program(int student_id);
void help_student(int student_id);
int student_waiting(int student_id);

int main() {
    pthread_t ta;
    pthread_t students[MAX_STUDENTS];
    int i, student_ids[MAX_STUDENTS];

    // Initialize semaphores
    sem_init(&sem_ta, 0, 0);
    sem_init(&sem_students, 0, 0);

    // Create TA thread
    pthread_create(&ta, NULL, ta_thread, NULL);

    // Create student threads
    for (i = 0; i < MAX_STUDENTS; i++) {
        student_ids[i] = i + 1;
        pthread_create(&students[i], NULL, student_thread, (void *)&student_ids[i]);
    }

    // Below should not happen unless a thread implodes

    // Destroy semaphores and mutex (garbage collect)
    sem_destroy(&sem_ta);
    sem_destroy(&sem_students);
    pthread_mutex_destroy(&mutex_chairs);

    return 0;
}

void *ta_thread(void *arg){
    pthread_exit(NULL);
}

void *student_thread(void *arg) {
    int student_id = *((int *)arg);

    while(1){
        program(student_id);
    }

    pthread_exit(NULL);
}

void program(int student_id) {
    printf("Student %d is programming.\n", student_id);
    // Simulate programming by sleeping for a random period of time
    int sleep_time = rand() % 5 + 1;
    sleep(sleep_time);
}

void help_student(int student_id){
    printf("Student %d is getting help from the TA.\n", student_id);
    // Simulate helping by sleeping for a random period of time
    sleep(help_time);
}

int student_waiting(int student_id){
    for(int i = 0; i < MAX_CHAIRS; i++){
        if(waiting_room[i] == student_id){ // Check if a student is already waiting for a chair
            return 1;
        }
    }
    return 0;
}