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
    int A, B, T, child_num;	// A = Argument 1 // B = Argument 2 // child_num = Child Number 
    pid_t childpid;		// Declare child process 
    childpid = getpid();	// Get child PID
    child_num = atoi(argv[1]); 	// Argument index 0 is the child number
    T = atoi(argv[2]);   	// Argument index 1 is maximum sleeptime m
    A = atoi(argv[3]); 		// Argument index 2 is first integer
    B = atoi(argv[4]); 		// Argument index 3 is second integer
    
    sleep(rand()%T);		// Sleep for random time mod T
    // Display child number and PID
    printf("I am child number %d with PID %d, ", child_num, childpid); 
    // Display arithmetic operations
    switch(child_num)
    {
    case 0: // SUM
	printf("the sum is %d\n", A + B); 
        return(1);
    case 1: // DIFFERENCE
        printf("the difference is %d\n", A - B);
        return(2);
    case 2: // DIVIDE (WITH REMANDER)
    	if (B == 0)	// Check for divide by zero	
    	{
    		printf("Divide by zero error\n");
    		exit(1);
    	}
    	printf("the quotient is %d and the remander is %d\n", A / B, A % B);
        return(3);
    case 3: // MULTIPLY
        printf("the product is %d\n", A * B);
        return(4);
    default:
		printf("An error has occured");
		exit(1);     
    }       // End switch
    exit(0);
}
