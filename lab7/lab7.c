
# include <stdio.h> 
# include <sys/types.h> 
# include <sys/ipc.h> 
# include <sys/sem.h> 
# include <unistd.h> 
# include <stdlib.h> 
# define NS 3 
# include <time.h>
 
 
union semun 
{ 
	int val; struct semid_ds *buf; ushort *array; 
}; 
int main(void) 
{ 
	int sem_id, sem_value, i; key_t ipc_key; 
	struct semid_ds sem_buf; 
	static ushort sem_array[NS] = {3, 1, 4}; 
	union semun arg; 
	ipc_key = ftok(".", 'S'); 
 
	/* Create semaphore */ 
	if ((sem_id = semget(ipc_key, NS, IPC_CREAT| IPC_EXCL | 0666)) == -1) 
	{ 
		perror ("semget: IPC | 0666"); 
 		exit(1); 
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
/* 	if (semctl(sem_id, 0, IPC_RMID, 0) == -1) 
	{ 
 		perror ("semctl: IPC_RMID"); 
 		exit(5); 
 	}*/  
} 

