/**************************************************************************/ 
/* PROGRAM NAME: acquire.c                                                */
/* CLASS:        CECS-326                                                 */
/* INSTRUCTOR:   Mr. Haney Williams                                       */
/* STUDENTS:     Cody Gildea                                              */
/*               Steven Le                                                */
/* DESCRIPTION: This program utilizes a parent program and child program  */
/* to demonstrate using 'locks' and 'critical state'  with processes.	  */
/**************************************************************************/ 
# include<sys/types.h>
# include<sys/stat.h>
# include<fcntl.h>
# include<stdio.h>
# include<stdlib.h>
# include<errno.h>

void main(int argc, char *argv[])
{
	char *fname;					// File name char
	int fd, sleeptime, n_try, value, count = 0;	// File, sleeptime, number tries, child value, count for attempts
	pid_t pid;					// Process ID
/*
	if (argc != 4) // If arguments are not 4 inputs
        {
                printf("Invalid inputs, requires 4 arguments.\n", argv[0]);
                exit(1);
        }*/
	pid = getpid();					// Get PID
	srand((unsigned)pid);
	value = atoi(argv[1]);				// Child value, argument 2
	fname = argv[2];				// File name, argument 3
	sleeptime = atoi(argv[3]);			// Sleeptime, argument 4
	n_try = atoi(argv[4]);				// Current number of tries, argument 5

	if (sleeptime <= 0)   // If argument sleeptime is less than or equal to 0, throw exception
        {
                printf("Input error.\n");
                printf("Sleeptime must be > 0\n");
                exit(1);
        }
	
	if (n_try <= 0)   // If argument n_try is less than or equal to 0, throw exception
        {
                printf("Input error.\n");
                printf("Number of tries  must be > 0\n");
                exit(1);
        }
	/* Acquire lock*/
	while ((fd = creat(fname, 0)) == -1 && errno == EACCES)
		if(++count < n_try)
			sleep(rand()%sleeptime);
		else
		{
		//	printf("\nUnable to generate.\n");
			kill(pid, value); // Kill process
		}
		/* Close file*/
		close (fd);
		//printf("\nFile %s has been created\n", fname);
}
