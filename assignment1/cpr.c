/* ------------------------------------------------ ------------
File: cpr.c

Last name: Petrucci
Student number: 300119235

Description: This program contains the code for creation
 of a child process and attach a pipe to it.
	 The child will send messages through the pipe
	 which will then be sent to standard output.

Explanation of the zombie process
(point 5 of "To be completed" in the assignment):

	(please complete this part);

------------------------------------------------------------- */
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

/* Prototype */
void createChildAndRead (int);

/* -------------------------------------------------------------
Function: main
Arguments: 
	int ac	- number of command arguments
	char **av - array of pointers to command arguments
Description:
	Extract the number of processes to be created from the
	Command line. If an error occurs, the process ends.
	Call createChildAndRead to create a child, and read
	the child's data.
-------------------------------------------------- ----------- */

int main (int ac, char **av)
{

 int processNumber; 
 if (ac == 2)
 {
 if (sscanf (av [1], "%d", &processNumber)== 1)
 {
    createChildAndRead(processNumber);
 }
    else fprintf(stderr, "Cannot translate argument\n");
 }
    else fprintf(stderr, "Invalid arguments\n");
    return (0);
}


/* ------------------------------------------------ -------------
Function: createChildAndRead
Arguments: 
	int prcNum - the process number
Description:
	Create the child, passing prcNum-1 to it. Use prcNum
	as the identifier of this process. Also, read the
	messages from the reading end of the pipe and sends it to 
	the standard output (df 1). Finish when no data can
	be read from the pipe.
-------------------------------------------------- ----------- */

void createChildAndRead(int prcNum)
{
	/*Calls the recursive helper function.
	Has a useless pid_t array that may be useful for some situations.*/
	pid_t temp[prcNum];
	pid_t pids = createChildAndReadHelper(prcNum, temp);
}

pid_t createChildAndReadHelper(int i, pid_t temp[])
{
	//Recursively creates a pid_t array for the forked proccesses

	char write_msg[BUFFER_SIZE] = "test :)";
 	char read_msg[BUFFER_SIZE];

	if(i != 0){
		temp[i] = fork();
		if(temp[i]==0){ //child
			//printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
			printf("Process %d begins\n",i);
			//WRITE TO PIPE HERE!
			int fd[2];
			pipe(fd);
			

			//Creates new child
			createChildAndReadHelper(i - 1, temp);

			exit(0);
		}

		else{ //parent
			
			//parent waits here for whatever i is equal to
			//READ TO PIPE HERE and write pipe here
			wait(NULL);
			printf("Process %d ends\n",i);
			exit(0);
		}
	}
	exit(0); //end recursive loop
}
