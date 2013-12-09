/**************************************************************************/ 
/* PROGRAM NAME: proj6.c                                                  */
/* CLASS:        CECS-326                                                 */
/* INSTRUCTOR:   Mr. Haney Williams                                       */
/* STUDENTS:     Cody Gildea                                              */
/*               Steven Le                                                */                                            
/* DESCRIPTION: This program utilizes creating pipes                      */
/**************************************************************************/ 
/* Unnamed pipe pipe.c */ 
/* Usage: pipe message_to_be_written. Parent write a message to child */ 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h> 

# define BUFSIZE 256 
void main(int argc, char *argv[]) 
{ 
   int f_des[2];                    
    /* Success: 0, failure: -1, sets errno. If successful, pipe returns two 
    integer file descriptors, filedes[0] and filedes[1], that reference two data streams */

    static char message[BUFSIZ];        // Set buff size
    char buffer[MAX_CANON];             // Set buffer to MAX_CANON
    char *c;                            // Character pointer
    int i,k, n, status, order; 
    pid_t childpid;                     // For child process ID
    /*
    if (argc < 4 || argc > 5) 
    { 
        printf ("\n Invalid input. Arguments must be 4 or 5\n"); 
        exit(1);
    } */
    if(strcmp(argv[1], "n") == 0)
    {
        if (argc != 5) 
        /* Check input arguments are exactly 5 */
        { 
            printf ("\n Arguments must be 5 when using a named pipe.\n"); 
            exit(1);
        }
        if (strlen(argv[4]) > 32)
        {
            printf ("\nInvalid input. The message cannot have a length greater than 32.\n"); 
            exit(1);
        } 
        if (strcmp(argv[3], "c") == 0) /* child -> parent */                
        {
            order = 0;
        }
        else if (strcmp(argv[3], "p") == 0) /* parent -> child */
        {
            order = 1;
        }
        else
        {
            printf("Invalid input for the order of the pipe.");
            exit(1);
        }
    }
    else if(strcmp(argv[1], "u") == 0)
    {
        if (argc != 4) 
        /* Check input arguments are exactly 4 */
        { 
            printf ("\n Arguments must be 4 when using a non named pipe.\n"); 
            exit(1);
        } 
        if (strlen(argv[3]) > 32)
        {
            printf ("\nInvalid input. The message cannot have a length greater than 32.\n"); 
            exit(1);
        } 
        if (strcmp(argv[2], "c") == 0) /* child -> parent */                
        {
            order = 0;
        }
        else if (strcmp(argv[2], "p") == 0) /* parent -> child */
        {
            order = 1;
        }
        else
        {
            printf("Invalid input for the order of the pipe.");
            exit(1);
        }
    }
    else
    {
        printf("Invalid input for the second argument. %s should be 'n' or 'u'.\n", argv[1]);
        exit(1);
    }




    /* generate pipe */
    if (pipe(f_des) == -1) 
    { 
        perror ("Pipe"); 
        exit(2); 
    } 
    if (order == 0)
    {
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
                //while ((wait(&status) == -1) && (errno == EINTR));
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
    } 
    else if (order == 1)
    {
        switch (fork()) 
        { 
            case -1: 
                perror ("Fork"); 
                exit(3); 
            case 0: /* In the child */ 
                close(f_des[1]); 
                if (read(f_des[0], message, BUFSIZ) != -1) 
                { 
                    printf ("Message received by child: *%s*\n", message); 
                    fflush(stdout); 
                } 
                else 
                { 
                    perror ("Read");
                    exit(4);
                } 
                break; 
            default: /* In the parent */ 
                close(f_des[0]); 
                if (write(f_des[1], argv[], strlen(argv[1])) != -1)
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
        }
    }
    exit(0); 
}
