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
 int fd[2];
 pipe(fd);

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
	//printf("parent process number is: %d\n", (int) prcNum);
	//printf("Parent PID is %ld\n", (long) getpid());


	//What this does is it creates five children frm the same parent
	//However, we want to have four parents, five children, get it?
	/*
	for(int i = 0; i<prcNum; i++) // loop will run n times (n=5)
    {
        if(fork() == 0)
        {
			printf("i is: %d\n", (int) i);
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());

				exit(0);
        }
    }*/
	//pid_t pids[prcNum];
	prcNum = prcNum -1; //decrement for each fork
	//pids[i] = fork();
    printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
	exit(0);

}
