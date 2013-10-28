/**************************************************************************/ 
/* PROGRAM NAME: proj3p.c                                                  */
/* CLASS:        CECS-326                                                 */
/* INSTRUCTOR:   Mr. Haney Williams                                       */
/* STUDENTS:     Cody Gildea                                              */
/*               Steven Le                                                */
/* DESCRIPTION: This program utilizes a parent program and child program  */
/* to demonstrate using locks  and wait with processes.					  */
/**************************************************************************/ 
# include<sys/types.h>
# include<sys/stat.h>
# include<fcntl.h>
# include<stdio.h>
# include<stdlib.h>
# include<errno.h>

main(int argc, char *argv[])
{
        pid_t pid, w;                 		  // For child process and wait time
        int k, status, num_tries, sleeptime;  // For child process number, status, number processes, and sleeptime
        char value[3];                		  // Char string for exec call

        if (argc !=3) // If arguments are not 4 inputs
           { 
                     printf("Invalid inputs, requires 4 arguments.\n", argv[0]); 
                     exit(1); 
           } 

        num_tries = atoi(argv[1]);        // Number of tries, argument 2
        sleeptime = atoi(argv[2]);        // Max sleeptime, argument 3
        
        if (num_tries <= 0)   // If argument n_try is less than or equal to 0, throw exception
        {
                printf("Input error.\n");
                printf("Number of tries  must be > 0\n");
                exit(1);
        }
        
        if (sleeptime <= 0)   // If argument sleeptime is less than or equal to 0, throw exception
        {
                printf("Input error.\n");
                printf("Sleeptime must be > 0\n");
                exit(1);
        }
        for (k=0;k<3;++k)
        {
                if((pid = fork()) == 0)        // Create child process
                {
                        sprintf(value, "%d",k);
                        execl("proj3c","child", value, argv[2], (char *)0);        // Call child program
                }
                else
                        printf("Forked child %d\n",pid);
        }
        /* Wait for children */
        while ((w=wait(&status)) && w != - 1)
        {
                if(w != -1) 
                        printf("Wait on PID: %d returns status of: %04X\n",w,status);
        }
        exit(0);
}