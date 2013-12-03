/**************************************************************************/ 
/* PROGRAM NAME: pipe.c (lab 8)                                           */
/* CLASS:        CECS-326                                                 */
/* INSTRUCTOR:   Mr. Haney Williams                                       */
/* STUDENTS:     Cody Gildea                                              */                                            
/* DESCRIPTION: This program utilizes creating pipes					  */
/**************************************************************************/ 
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
	/* Success: 0, failure: -1, sets errno. If successful, pipe returns two 
	integer file descriptors, filedes[0] and filedes[1], that reference two data streams */

	static char message[BUFSIZ]; 		// Set buff size
	char buffer[MAX_CANON]; 			// Set buffer to MAX_CANON
	char *c; 							// Character pointer
	int i,k, n; 
	pid_t childpid; 					// For child process ID
 	if (argc !=2) 
 	/* Check input arguments are 2 */
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
 		case -1: /* Fork error*/
 			perror ("Fork"); 
 			exit(3); 
 		case 0: /* In the child */ 
 			close(f_des[0]); 
		 	if (write(f_des[1], argv[1], strlen(argv[1])) != -1)
		 	/* success: number of bytes written, 
			failure: -1, sets errno. Write nbyte bytes from the buffer 
			referenced by buf using the file descriptor pecified by filedes. */
			{ 
	 			printf ("Message sent by child: [%s]\n", argv[1]);
				fflush(stdout); 
			} 
	 		else 
			{ /* Write error*/
				perror ("Write"); 
				exit(5); 
			} 
	 		break; 
 		default: /* In the parent */ 
	 		close(f_des[1]); 
			if (read(f_des[0], message, BUFSIZ) != -1) 
			/* success: number of bytes read, failure: -1, sets errno. 
		 	All reads are initiated from current position. Read nbyte bytes 
		 	from the open file associated with the file descriptor filedes 
		 	into the buffer referenced by buf. */
			{ 
				printf ("Message received by parent: *%s*\n", message); 
				fflush(stdout); 
			} 
	 		else 
	 		{ /* Read error*/
	 			perror ("Read"); 
	 			exit(4);
	 		} 	
 	} 
 	exit(0); 
}
