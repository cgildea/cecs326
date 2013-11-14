
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
	int sem_id, sem_value, i, j, NS, count; 
	key_t ipc_key; 
	char *ropt;

	struct semid_ds sem_buf; 
	ushort sem_array[NS]; 
	union semun arg; 
	ipc_key = ftok(".", 'S'); 

	if ((strcmp(argv[1], 'n') || strcmp(argv[1], 'r')) == 0)
	{
		ropt = argv[1];
	}
	else
	{
		printf("Invalid input for the second argument. %s should be 'n' or 'r'.\n", argv[1]);
		exit(1);
	}
	NS = atoi(argv[2]);

	for (j=0;j<NS;++j)
	{
		sem_array[j] = atoi(argv[j+3]);
		count++;
	}
	if (NS != count)
	{
		printf("Invalid input.  The number of semaphores, %d must equal the number of values, %d.\n", NS, count);
		exit(1);
	}

 
	/* Create semaphore */ 
	if (ropt == 'n')
	{
		if ((sem_id = semget(ipc_key, NS, IPC_CREAT | IPC_EXCL | 0666)) == -1) 
		{ 
			perror ("semget: IPC | 0666"); 
	 		exit(1); 
	 	} 
 	}
 	if (ropt == 'r')
 	{
 		if ((sem_id = semget(ipc_key, NS, IPC_CREAT | 0666)) == -1) 
		{ 
			perror ("semget: IPC | 0666"); 
	 		exit(1); 
	 	} 
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
 	if (semctl(sem_id, 0, IPC_RMID, 0) == -1) 
	{ 
 		perror ("semctl: IPC_RMID"); 
 		exit(5); 
 	}
} 

