/*********************************************************************/
/* Cody Gildea 008933663 CECS 326 				     */
/* PROGRAM: lab5p.c 						     */
/* DESCRIPTION: This program demonstrates the use of wait calls in a */
/* parent and child program generating processes		     */
/*********************************************************************/
# include <stdio.h> 
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
main(int argc, char *argv[])
{
	pid_t pid, w;		// For child process and wait time
	int k, status, N, T;	// For for, status, number processes, and sleeptime
	char value[3];		// Char string for exec call

	if (argc !=3) // If arguments are not 4 inputs
   	{ 
     		printf("Invalid inputs, requires 3 arguments.\n", argv[0]); 
     		exit(1); 
   	} 

	N = atoi(argv[1]);	// Number of child processes, argument 2
	T = atoi(argv[2]);	// Max sleeptime, argument 3
	
	if (N > 19 || N <= 0) 	// If argument N is less than 20, 0, or negative, throw exception
   	{ 
     		printf("Input error.\n");
     		printf("Maximum processes  N must be < 20 and > 0.\n"); 
     		exit(1); 
   	}
	if (T > 49 || T <= 0) 	// If argument T is greater than 50, 0, or negative, throw exception
   	{ 
     		printf("Input error.\n");
     		printf("Maximum sleeptime m must be < 50 and > 0.\n"); 
     		exit(1); 
   	}
	for (k=0;k<N;++k)
	{
		if((pid = fork()) == 0)	// Create child process
		{
			sprintf(value, "%d",k);
			execl("lab5c","child", value, argv[2], (char *)0);	// Call child program
		}
		else
			printf("Forked child %d\n",pid);
	}
	/* Wait for children */
	while ((w=wait(&status)) && w != - 1)
	{
		if(w != -1) 
			printf("Wait on PID: %d returns status of: %04X\n",w,status);
	}
	exit(0);
}
