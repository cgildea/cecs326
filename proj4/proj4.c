/**************************************************************************/ 
/* PROGRAM NAME: proj4.c                                                  */
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
 
 
union semun 
{ 
	int val; 
	struct semid_ds *buf; 
	ushort *array; 
}; 
int main(int argc, char *argv[]) 
{ 
	int sem_id, sem_value, i, j, NS;	// Semaphore ID, Semaphore value, i and j for for statement, Number of Semaphores
	key_t ipc_key; 						// Key for Semaphore
	struct semid_ds sem_buf;			// Allows access for Semaphore set and reference to the array of type sem 			
	union semun arg; 

	ipc_key = ftok(".", 'S'); 			// Generate a key from a pathname

	/* Check input arguments are at least 4 */
	if (argc < 4)
	{
		printf("Invalid input.  The number of arguments must be at least 4.\n");
		exit(1);
	}
	
	NS = atoi(argv[2]);					// Number of Semaphores, argument 3
	ushort sem_array[NS]; 				// Declare Semaphore array with number of Semaphores

	/* Check to see if the number of values matches the number of Semaphores */
	if (argc != (NS + 3))
	{
		printf("Invalid input.  The number of semaphores, %d must equal the number of values.\n", NS);
		exit(1);
	}

	/* Create semaphore */ 
	if (strcmp(argv[1], "n") == 0) 		// Create Semaphore without remove
	{
		if ((sem_id = semget(ipc_key, NS, IPC_CREAT | 0666 | IPC_EXCL)) == -1) 
		{ 
			perror ("semget: IPC | 0666"); 
	 		exit(1); 
	 	} 
 	}
 	else if (strcmp(argv[1], "r") == 0)	// Create Semaphore with remove
 	{
 		if ((sem_id = semget(ipc_key, NS, IPC_CREAT | 0666)) == -1) 
		{ 
			perror ("semget: IPC | 0666"); 
	 		exit(1); 
	 	} 
	 	if (semctl(sem_id, 0, IPC_RMID, 0) == -1) 
		{ 
 			perror ("semctl: IPC_RMID"); 
 			exit(5); 
 		}
 	}
 	/* Throw error if 2nd argument is not 'r' or 'n' */
 	else
	{
		printf("Invalid input for the second argument. %s should be 'n' or 'r'.\n", argv[1]);
		exit(1);
	}

	/* Fill sem_array with unsigned short values from command line up to the number of Semaphores */
	for (j=0;j<NS;j++)
	{
		sem_array[j] = (unsigned short) strtoul(argv[j+3], NULL, 0);
	}
	
 	printf ("Semaphore identifier %d\n", sem_id); 
	/* Set arg (the union) to the address of the storage location for */ 
	/* returned semid_ds value */ 
 
 	arg.buf = &sem_buf; 
 	if (semctl(sem_id, 0, IPC_STAT, arg) == -1) 
	{ 
 	perror ("semctl: IPC_STAT"); 
 	exit(2); 
 	} 
 	printf ("Create %s", ctime(&sem_buf.sem_ctime)); 
 
 	/* Set arg (the union) to the address of the initializing vector */ 
 	arg.array = sem_array; 
 
 	if (semctl(sem_id, 0, SETALL, arg) == -1) 
	{ 
 	perror("semctl: SETALL"); 
 	exit(3); 
 	} 
 	for (i=0; i<NS; ++i)
	{ 
 		if ((sem_value = semctl(sem_id, i, GETVAL, 0)) == -1)
		 { 
 			perror("semctl : GETVAL"); 
 			exit(4); 
 		} 
 		printf ("\nSemaphore %d has value of %d\n",i, sem_value); 
 	} 
 	/* remove semaphore */ 
 	/*if (semctl(sem_id, 0, IPC_RMID, 0) == -1) 
	{ 
 		perror ("semctl: IPC_RMID"); 
 		exit(5); 
 	}*/
  exit(0);
} 

