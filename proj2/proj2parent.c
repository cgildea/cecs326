/**************************************************************************/ 
/* PROGRAM NAME: project2.c						  */
/* CLASS:        CECS-326						  */
/* INSTRUCTOR:   Mr. Haney Williams					  */
/* STUDENTS:     Cody Gildea						  */
/*               Steven Le						  */
/* DESCRIPTION: This program utilizes a parent program and child program. */
/**************************************************************************/ 
# include<stdio.h>
# include<stdlib.h>
# include<sys/types.h>
# include<unistd.h>

int main(int argc, char *argv[]) 
{
    int i, A, B, T, n;		// A = Argument 1 // B = Argument 2 // T = Sleeptime // n = Number of processes 
    pid_t childpid;		// Child PID
    char child_num[3]; 		// Character array for child number
   
    if (argc !=4) 		// If arguments are not 4 inputs
    { 
      printf("Invalid inputs, requires 4 arguments.\n", argv[0]); 
      exit(1); 
    }
    n = 4;     // Number of processes = 4
    T = atoi(argv[1]);   // Argument index 1 is maximum sleeptime T
    A = atoi(argv[2]); // Argument index 2 is first integer
    B = atoi(argv[3]); // Argument index 3 is second integer

    if (T > 50 || T <= 0) // If argument T is greater than 50, 0, or negative, throw exception
    { 
      printf("Input error.\n");
      printf("Maximum sleeptime m must be <= 50 and > 0.\n"); 
      exit(1); 
    }
    srand(time(NULL));
    // Print parent process, max sleep, and the two arguments
    printf("I am parent process, the maximum sleep time is %d and the two numbers are %d and %d.\n", T, A, B);
    // Sleep using T	
    sleep(rand()%T); 
    // Generate child processes using fork()
    for (i=0; i<n;i++) 
    {  
        switch(childpid = fork())
        {
         case 0:
         	  sprintf(child_num, "%d", i);
         	  // Invoke child program, pass child number, sleeptime and arithmetic arguments
         	  execl("proj2child", "child", child_num, argv[1], argv[2], argv[3], (char *)0);
         	  // If not, exec failure
         	  perror("Exec failure");
              return(1);
         case -1:
         	  // Fork failed
              perror ("The fork failed.\n"); 
          	  return(2); 
	 default:
	      // Print Forked Child 
	      printf("\nForked child %d\n", childpid);    
         }    // End switch
    } // End for
    exit(0);
}
