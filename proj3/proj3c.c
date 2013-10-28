/**************************************************************************/ 
/* PROGRAM NAME: proj3c.c                                                 */
/* CLASS:        CECS-326                                                 */
/* INSTRUCTOR:   Mr. Haney Williams                                       */
/* STUDENTS:     Cody Gildea                                              */
/*               Steven Le                                                */
/* DESCRIPTION: This program utilizes a parent program and child program  */
/* to demonstrate using 'locks'  and 'wait' with processes.				  */
/**************************************************************************/ 
# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h>
# include <sys/wait.h>
# include<sys/stat.h>
# include<errno.h>
# include<fcntl.h>
main(int argc, char *argv[])
{
        pid_t pid, pid_c w;                						// For child process
        int ret_value, num_tries, sleeptime, i, value, status;        // Ret_value and sleeptime
	char *fname;						  			// File name
	char *lockfname = "lock1";								// Lock file name
	char sleepChar[3];
		
	value = atoi(argv[1]);
        fname = argv[2];
        num_tries = atoi(argv[3]);        // Number of tries, argument 3
        sleeptime = atoi(argv[4]);        // Max sleeptime, argument 4

        pid = getpid();                // Get the process ID
        srand((unsigned) pid); 
		
		for (i = 0; i<num_tries;++i)
		{
			if((pid_c = fork()) == 0)
			{
				sprintf(sleepChar, "%d", sleeptime);
				execlp("acquire", "acquire", lockfname, sleepChar, "1", (char*)0);
			}
			while ((w=wait(&status)) && w != - 1)
			{
                		if(w != -1) {
				} 
			}
			if (status == 0)
				break;
			else
				sleep(rand()%sleeptime);
		}
		 if(i == num_tries)
		 {
			printf("\nUnable to obtain lockfile\n");
			exit(value);
         }
		 if ((pid_c = fork()) == 0)
		 {
			execlp("/bin/cat", "/bin/cat", fname, (char*)0);
		 }
		 while ((w=wait(&status)) && w != - 1)
		{
            		if(w != -1) {
			} 
		}
		 if ((pid_c = fork()) == 0)
		 {
			sprintf(sleepChar, "%d", sleeptime);
			execlp("release", "release", lockfname, sleepChar, "1", (char*)0);
		 }
		 while ((w=wait(&status)) && w != - 1)
		{
            		if(w != -1) {
			} 
		}
		 if(status == 0)
			exit(getpid()&255);
}
