/**************************************************************************/ 
/* PROGRAM NAME: proj5.c                                                  */
/* CLASS:        CECS-326                                                 */
/* INSTRUCTOR:   Mr. Haney Williams                                       */
/* STUDENTS:     Cody Gildea                                              */
/*               Steven Le                                                */
/* DESCRIPTION: This program utilizes creating and removing semaphores	  */
/**************************************************************************/ 
# include <stdio.h> 
# include <sys/types.h> 
# include <sys/ipc.h> 
# include <sys/sem.h> 
# include <unistd.h> 
# include <stdlib.h> 
# include <time.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

/* Define the C variable 'MAX_CANNON' for the char buffer */
#ifndef MAX_CANON
#define MAX_CANON 8192
#endif													 

 
 
void set_sembuf_struct(struct sembuf *s, int semnum, int semop, int semflg);

int main(int argc, char *argv[]) 
{ 
	pid_t pid, ppid, childpid, w;                 		 // For process ID, parent process ID, child process, and wait
	pid_t leader = getpid();							 // Used to make sure the child process finishes before the parent is killed
	int semid, semop_ret, sem_value, i, j, opt;			 // Semaphore ID, Semaphore value, i and j for for statement, and Semaphore option
	int N, status, k;									 // Number of processes, the status for wait, and the delay paramater
	char buf_num[MAX_CANON], *c_ptr;					 // Character buffer and pointer to navigate it
	key_t ipc_key; 										 // Key for Semaphore
	struct semid_ds sem_buf;							 // Allows access for Semaphore set and reference to the array of type sem 	

	/* Check input arguments are 4 */
	if (argc != 4)
	{
		printf("Invalid input.  The number of arguments must be 4.\n");
		exit(1);
	}
	/* Make sure number of precesses is more than 0 */
	if(atoi(argv[1]) > 0)
	{
		N = atoi(argv[1]);
	}
	else
	{
		printf("Invalid input. %d(N) must be greater then 0.\n", atoi(argv[1]));
		exit(1);
	}

	/* Declare the operation for semaphore protection */
	if (strcmp(argv[2], "n") == 0) /* No semaphore protection */		
	{
		opt = 0;
	}
	else if (strcmp(argv[2], "s") == 0) /* Semaphore protection */
 	{
 		opt = 1;
 	}
 	else
	{
		printf("Invalid input for the second argument. %s should be 'n' or 's'.\n", argv[1]);
		exit(1);
	}

	/* Initialize the delay parameter, 'k', if it is greater than 0 */
	if(atoi(argv[3]) > 0)
		k = atoi(argv[3]);
	else
	{
		printf("Invalid input. %d(k) must be greater then 0.\n", atoi(argv[3]));
		exit(1);
	}

	/* Decalre semaphore wait and increment */
	struct sembuf semwait[1]; 
 	struct sembuf semsignal[1];

 	/* Initialize semaphore element to 1 */ 
 	set_sembuf_struct(semwait, 0, -1, 0); 
 	set_sembuf_struct(semsignal, 0, 1, 0); 

	ipc_key = ftok(".", 'S'); 			// Generate a key from a pathname
	
	/* Create semaphore */
	/* A semaphore is always created reguardless of semaphore procetion. It is only used if k = s */ 
	if ((semid = semget(ipc_key, 1, IPC_CREAT | IPC_EXCL | 0666)) == -1) 
	{
        perror ("semget: IPC | 0666");
        exit(1);
	}

	/* Attempt to increment the semaphore */
	if(semop(semid, semsignal, 1) == -1) 
	{
	    printf("%ld: semaphore increment failed - %s\n", (long)getpid(), strerror(errno)); 
	    /* Remove the semaphore if unable to increment */
	        if (semctl(semid, 0, IPC_RMID) == -1) 
	            printf ("%ld: could not delete semaphore - %s\n", (long)getpid(), strerror(errno)); 
	            exit(1); 
	}
	
	/* Create the processes based on the value of 'N' */
	childpid = 0;
	for(i = 1; i < N; i++)
	{
		if(childpid = fork()) break; 
	}

	/* If semaphore protection is used, decrement the semaphore and enter it */
	if(opt)
	{
		while (( (semop_ret = semop(semid, semwait, 1) ) == -1) && (errno ==EINTR)); 
		    if (semop_ret == -1) 
		        printf ("%ld: semaphore decrement failed - %s\n", (long)getpid(), strerror(errno)); 
	}

	/* Create the output message and put in into a character buffer */
	sprintf(buf_num,"i: %d: process ID: %6ld parent ID: %6ld child ID: %6ld\n",i,(long)getpid(), (long)getppid(), (long)childpid);

	/* Direct the pointer to the char buffer */ 
	c_ptr = buf_num;

	/* Specifies the buffer to be used by the stream for I/O operations, which becomes a    */
	/* fully buffered stream. Or, alternatively, if buffer is a null pointer, buffering is  */
	/* disabled for the stream, which becomes an unbuffered stream. 						*/
	setbuf(stdout, NULL);

	/* Cycle through the char buffer using the pointer until it points to NULL */
	while (*c_ptr != '\0')
	{
		fputc(*c_ptr, stderr);
		/* Sleep in usec microsecond using the delay adjustment parameter */
		usleep(k);
		c_ptr++;
	}

	/* If semaphor protection is enabled, increment the semaphore */ 
	if(opt)
	{
		while ( ( (semop_ret = semop(semid, semsignal, 1) ) == -1) && (errno == EINTR) ); 
			if (semop_ret == -1) 
			    printf ("%ld: semaphore increment failed - %s\n", (long)getpid(), strerror(errno));
	}

	/* Wait for the child process to complete before the parent is killed */
	waitpid(childpid, &status, 0);

	/* Once the process has completed, remove the semaphore */
	if(leader == getpid())
	{
        if(semctl(semid, 0, IPC_RMID) == -1)
        {
            printf("%ld: couldn't delete semaphore - %s\n", (long)getpid(), strerror(errno));
            exit(1);
        }
    }
  exit(0);
} 
/* Initializing the semaphore buffer */
void set_sembuf_struct(struct sembuf *s, int num, int op, int flg) 
 { 
 	s->sem_num = (short) num; 
 	s->sem_op = op; 
	s->sem_flg = flg; 
 	return; 
 };

