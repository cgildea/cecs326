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

#ifndef MAX_CANON
#define MAX_CANON 8192
#endif

 
 
void set_sembuf_struct(struct sembuf *s, int semnum, int semop, int semflg);

int main(int argc, char *argv[]) 
{ 
	pid_t pid, ppid, childpid, w;                 		 // For child process
	int semid, semop_ret, sem_value, i, j;			 // Semaphore ID, Semaphore value, i and j for for statement
	int N, status, k;
	char opt, buf_num[MAX_CANON], *c_ptr;
	key_t ipc_key; 									// Key for Semaphore
	struct semid_ds sem_buf;						// Allows access for Semaphore set and reference to the array of type sem 	

	/* Check input arguments are 4 */
	if (argc != 4)
	{
		printf("Invalid input.  The number of arguments must be 4.\n");
		exit(1);
	}
	if(atoi(argv[1]) > 0)
	{
		N = atoi(argv[1]);
	}
	else
	{
		printf("Invalid input. %d(N) must be greater then 0.\n", atoi(argv[1]));
		exit(1);
	}

	if(atoi(argv[3]) > 0)
		k = atoi(argv[3]);
	else
	{
		printf("Invalid input. %d(k) must be greater then 0.\n", atoi(argv[3]));
		exit(1);
	}




	struct sembuf semwait[1]; 
 	struct sembuf semsignal[1];

 	/* Initialize semaphore element to 1 */ 
 	set_sembuf_struct(semwait, 0, -1, 0); 
 	set_sembuf_struct(semsignal, 0, 1, 0); 


	ipc_key = ftok(".", 'S'); 			// Generate a key from a pathname

	
	/* Create semaphore */ 
	if (strcmp(argv[2], "n") == 0) 		
	{
		childpid = 0;
		for(i = 1; i < N; i++){
			if(childpid = fork()) break; 
		}
		sprintf(buf_num,"i: %d: process ID: %6ld parent ID: %6ld child ID: %6ld",i,(long)getpid(), (long)getppid(), (long)childpid);

		c_ptr = buf_num;


		while (*c_ptr != '\0')
		{
			setbuf(stdout, NULL);
			fputc(*c_ptr, stderr);

			usleep(k);

			//printf("%c", *c_ptr);
			/*
			for(c1 = 0; c1 < k; c1++)
			{
				for(c2=0 c2 < 50000; c2++);
			}*/
			c_ptr++;
		}
		//fputc(" ", stderr);

		if (childpid > 0)
			while ((k=wait(&status)) && k != - 1);
 	}
 	else if (strcmp(argv[2], "s") == 0)
 	{
 		if ((semid = semget(ipc_key, 1, IPC_CREAT | IPC_EXCL | 0666)) == -1) 
	 	{
	            perror ("semget: IPC | 0666");
	            exit(1);
	    }
 		for (j = 1; j < N; j++)
 		{
	 		
	        if(semop(semid, semsignal, 1) == -1) 
	        {
	               printf("%ld: semaphore increment failed - %s\n", (long)getpid(), strerror(errno)); 
	               if (semctl(semid, 0, IPC_RMID) == -1) 
	                       printf ("%ld: could not delete semaphore - %s\n", (long)getpid(), strerror(errno)); 
	               exit(1); 
	        }

	        while (( (semop_ret = semop(semid, semwait, 1) ) == -1) && (errno ==EINTR)); 
	        	if (semop_ret == -1) 
	            	printf ("%ld: semaphore decrement failed - %s\n", (long)getpid(), strerror(errno)); 

	        childpid = 0;
			for(i = 1; i < N; i++){
				if(childpid = fork()) break; 
			}
			sprintf(buf_num,"i: %d: process ID: %6ld parent ID: %6ld child ID: %6ld",i,(long)getpid(), (long)getppid(), (long)childpid);

			c_ptr = buf_num;


			while (*c_ptr != '\0')
			{
				setbuf(stdout, NULL);
				fputc(*c_ptr, stderr);
				usleep(k);
				c_ptr++;
			}

			

	        while ( ( (semop_ret = semop(semid, semsignal, 1) ) == -1) && (errno == EINTR) ); 
	        if (semop_ret == -1) 
	                printf ("%ld: semaphore increment failed - %s\n", (long)getpid(), strerror(errno));


	         while ((w=wait(&status)) && w != - 1);
     	}

 	}
 	/* Throw error if 2nd argument is not 'r' or 'n' */
 	else
	{
		printf("Invalid input for the second argument. %s should be 'n' or 's'.\n", argv[1]);
		exit(1);
	}
  exit(0);
} 
void set_sembuf_struct(struct sembuf *s, int num, int op, int flg) 
 { 
 	s->sem_num = (short) num; 
 	s->sem_op = op; 
	s->sem_flg = flg; 
 	return; 
 };

