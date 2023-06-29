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
void help_student();
int student_waiting(int student_id);
void add_waiting(int student_id);
void remove_waiting(int student_id);

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
    for (i = 0; i < MAX_STUDENTS - 1; i++) {
        student_ids[i] = i;
        pthread_create(&students[i], NULL, student_thread, (void *)&student_ids[i]);
    }

    for (i = 0; i < MAX_STUDENTS; i++) { // Required for continuity
        pthread_join(students[i], NULL);
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

    while(student_waiting(student_id) == 0){
        program(student_id);
        // Need help from TA

        pthread_mutex_lock(&mutex_chairs); // Mutex ensures that only one student can run the chair check at a time

        if(students_waiting < MAX_CHAIRS){
            add_waiting(student_id);
            students_waiting++;


            // TODO: Add TA semaphore calling here


            printf("Student %d is getting help from the TA.\n", student_id);

        }

        else{
            printf("Student %d cannot get help from the TA.\n", student_id);
        }

        pthread_mutex_unlock(&mutex_chairs); // Mutex ensures that only one student can run the chair check at a time

    }
    return 0;
}

void program(int student_id) {
    printf("Student %d is programming.\n", student_id);
    // Simulate programming by sleeping for a random period of time
    int sleep_time = rand() % 10 + 1;
    sleep(sleep_time);
}

void help_student(){
    printf("TA is helping a student.\n");
    // Simulate helping by sleeping for a random period of time
    sleep(help_time);
}

int student_waiting(int student_id){ // Check if a student is already waiting for a chair
    for(int i = 0; i < MAX_CHAIRS; i++){
        if(waiting_room[i] == student_id){ 
            return 1;
        }
    }
    return 0;
}

void add_waiting(int student_id){ // Adds a student to the waiting list
    for(int i = 0; i < MAX_CHAIRS; i++){
        if(waiting_room[i] == 0){ 
            waiting_room[i] = student_id;
        }
    }
}

void remove_waiting(int student_id){ // Removes a student from the waiting list
    for(int i = 0; i < MAX_CHAIRS; i++){
        if(waiting_room[i] == student_id){ 
            waiting_room[i] = 0;
        }
    }
}