/******************************************************************************/ 
/* Cody Gildea 008933663 CECS 326					      */
/* PROGRAM: lab2.c                                                            */ 
/* DESCRIPTION: This program generates a chain of processes                   */ 
/* using fork(). The number of processes n is a command line argument.        */ 
/* Each process sleeps for a random time less than 10 seconds then prints out */ 
/* process ID, parent ID, and child ID 					      */ 
/******************************************************************************/

# include<stdio.h>
# include<stdlib.h>
# include<sys/types.h>
# include<unistd.h>

int main(int argc, char *argv[])
{
	int i, m, n, sleeptime, seed;
	pid_t childpid;
	
	if(argc != 3)//Checks for 3 arguments for input
	{
		printf("\nUsage: %s processes\nNot enough arguments.\n", argv[0]);
		exit(1);
	}
	//number of processes
	n = atoi(argv[1]);
	//maximum sleep time
	m = atoi(argv[2]);
	
	//validate that n < 10 but greater than 0 and m < 20 but greater than 0
	if(n > 9 || m > 19 || n <= 0 || m <= 0)
	{
		printf("\nInvalid arguments used. Runtime failed.\n");
		exit(1);
	}
	childpid = 0;
	for(i=0;i<n;i++)
		if(childpid = fork()) break;//break if forked
	//throw error is fork failed
	if(childpid == -1)
	{
		perror("\nThe fork failed\n");
		exit(1);
	}
	//display the process ID's, parent ID's, and child ID's
	printf("\n%d: process ID: %6ld	parent ID: %6ld	child ID: %6ld",i,(long)getpid(),
		(long)getppid(), (long)childpid);
	seed = (int)(getpid()+childpid);

	srand(seed);

	/*Since each process has a different childpid, using the childpid
	  as the seed number will restart the random function.
	  Therefore, each process will have a different sleeptime.
	*/
	
	sleeptime = rand()%m;
	sleep(sleeptime);
	printf(" sleep = %d\n", sleeptime);
	exit(0);
}
