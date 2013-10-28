/*********************************************************************/
/* Cody Gildea 008933663 CECS 326                                    */
/* PROGRAM: lab5c.c                                                  */
/* DESCRIPTION: This program demonstrates the use of wait calls in a */
/* parent and child program generating processes                     */
/*********************************************************************/ 
# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h>
# include <sys/wait.h>
main(int argc, char *argv[])
{
	pid_t pid;		// For child process
	int ret_value, T;	// Ret_value and sleeptime

	T = atoi(argv[1]);	// Get sleeptime from parent program, argument 2

	pid = getpid();		// Get the process ID
	ret_value =(int)(pid %256);
	srand((unsigned) pid); 
	sleep(rand() %T);	// Sleep random up to max sleeptime 
	if(atoi(*(argv + 1))%2)
	{
		printf("Child %d is terminating with signal 009\n",pid); // Child displays PID
		kill(pid,9);	// Kill child process
	}
	else
	{
		printf("child %d is terminating with exit(%04X)\n",pid, ret_value); // Child terminates with exit ret_value
	exit(ret_value);
	}
}
