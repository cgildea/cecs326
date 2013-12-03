/* Unnamed pipe pipe.c */ 
/* Usage: pipe message_to_be_written. Parent write a message to child */ 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h> 
void main(int argc, char *argv[]) 
{ 
	int f_des[2]; 
	static char message[BUFSIZ]; 
	char buffer[MAX_CANON]; 
	char *c; 
	int i,k, n; pid_t childpid; 
 	if (argc !=2) 
	{ 
		printf ("\n Usage: %s message\n", *argv); 
		exit(1);
	} 
 	/* generate pipe */
	if (pipe(f_des) == -1) 
	{ 
		perror ("Pipe"); 
		exit(2); 
	} 
 	switch (fork())
	{ 
 		case -1: perror ("Fork"); exit(3); 
 		case 0: /* In the child */ 
 		close(f_des[1]); 
		if (read(f_des[0], message, BUFSIZ) != -1) 
		{ 
			printf ("Message received by child: *%s*\n", message); 
			fflush(stdout); 
		} 
 		else { perror ("Read"); exit(4);} break; 
 		default: /* In the parent */ 
	 	close(f_des[0]); 
	 	if (write(f_des[1], argv[1], strlen(argv[1])) != -1)
		{ 
 			printf ("Message sent by parent: [%s]\n", argv[1]);
			fflush(stdout); 
		} 
 		else 
		{ 
			perror ("Write"); 
			exit(5); 
		} 
 	} 
 	exit(0); 
}
