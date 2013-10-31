/**************************************************************************/ 
/* PROGRAM NAME: release.c                                                */
/* CLASS:        CECS-326                                                 */
/* INSTRUCTOR:   Mr. Haney Williams                                       */
/* STUDENTS:     Cody Gildea                                              */
/*               Steven Le                                                */
/* DESCRIPTION: This program utilizes a parent program and child program  */
/* to demonstrate using 'locks' and 'critical states  with processes.	  */
/**************************************************************************/ 
# include<sys/types.h>
# include<sys/stat.h>
# include<fcntl.h>
# include<stdio.h>
# include<stdlib.h>
# include<errno.h>

void main(int argc, char *argv[])
{
	char *fname;					// File name 
	int fd, sleeptime, n_try, count = 0;		// File, sleeptime, number tries, count
	pid_t pid;					// Process ID
	/*
	if (argc != 4) // If arguments are not 4 inputs
        {
                printf("Invalid inputs, requires 4 arguments.\n", argv[0]);
                exit(1);
        }*/
	pid = getpid();					// Get PID
	srand((unsigned)pid);
	fname = argv[1];				// File name, argument 2
	sleeptime = atoi(argv[2]);			// Sleeptime, argument 3
	n_try = atoi(argv[3]);				// Number of tires, argument 4

	if (sleeptime <= 0)   // If argument sleeptime is less than or equal to 0, throw exception
        {
                printf("Input error.\n");
                printf("Sleeptime must be > 0\n");
                exit(1);
        }
	if (n_try <= 0)   // If argument n_try is less than or equal to 0, throw exception
        {
                printf("Input error.\n");
                printf("Number of tries must be > 0\n");
                exit(1);
        }
	/* Release the file*/
	while (unlink(fname) != 0)
		if(++count < n_try) 
			sleep(sleeptime); /* Sleep*/
		else 
		{
			//printf("\nCannot release file\n");
			exit(-1);
		}
		//printf("\nFile is released\n");
}
