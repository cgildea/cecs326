/*********************************************************************/
/* Cody Gildea 008933663 CECS 326                                    */
/* PROGRAM: lab4a.c                                                  */
/* DESCRIPTION: This program demonstrates more use of exec calls and */
/* the fork() function.                                              */
/*********************************************************************/

# include <stdio.h> 
# include <unistd.h> 
void main() 
{ 
	static char *mesg[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"}; 
 	int display(char *), i; 
 
 	for (i=0; i<10; ++i) 
 		display(mesg[i]); 
	sleep(2); 
} 
int display(char *m) 
{ 
	char err_msg[25]; 
	switch (fork()) 
	{ 
	case 0: 
 		execlp("/bin/echo", "echo", m, (char *) NULL); 
 		sprintf (err_msg, "%s Exec failure", m); 
 		perror(err_msg); return(1); 
 	case -1: 
 		perror ("Fork failure"); return(2); 
 	default: 
 		return(0); 
 	} 
}

