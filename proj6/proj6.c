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

    mode_t fifo_mode = S_IRUSR | S_IWUSR; 
    int fd, status, child, order; 
    char buf[BUFSIZE]; 
    unsigned strsize; 
    char *inputMessage;
    char *pipeName;
    
    if (argc < 4 || argc > 5) 
    { 
        printf ("\n Invalid input. Arguments must be 4 or 5\n"); 
        exit(1);
    }
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
            printf("\nInvalid input for the order of the pipe.\n");
            exit(1);
        }
        pipeName = argv[2];
        inputMessage = argv[4];
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
            printf("\nInvalid input for the order of the pipe.\n");
            exit(1);
        }
        inputMessage = argv[3];
        pipeName = "FIFO";
    }
    else
    {
        printf("\nInvalid input for the second argument. %s should be 'n' or 'u'.\n", argv[1]);
        exit(1);
    }


    /* generate a named pipe with r/w for user */ 
    if ((mkfifo(pipeName,fifo_mode) == -1) && (errno != EEXIST)) /* EEXIST -> file already exists*/
        /* success: 0, failure: -1, sets errno. mkfifo 
        creates the FIFO file referenced by path; mode: File mode bits: 
        S_IRUSR read permission, owner. S_IWUSR write permission, owner */
    { /* Pipe error*/
        perror ("Pipe"); 
        exit(1); 
    } 

    if (order == 0)
    {
        if (( child = fork()) == -1) 
        { /* Fork error*/
            perror ("Fork"); 
            exit(1); 
        } 
        else if (child == 0)
        { 
            printf ("\n Child %ld is about to send the message [%s] to %s", (long)getpid(), inputMessage, pipeName); 
            if ((fd = open(argv[1], O_WRONLY)) == -1) /* Open for writing only*/
            { /* Open error*/
                perror("\nChild cannot open FIFO"); 
                exit(1);
            } 
            /* In the child */ 
            sprintf (buf, "\n*%s* from child %ld\n", inputMessage, (long)getpid()); 
            strsize = strlen(buf) + 1; 
            if (write(fd, buf, strsize) != strsize) 
                /* success: number of bytes written, 
                failure: -1, sets errno. Write nbyte bytes from the buffer 
                referenced by buf using the file descriptor pecified by filedes. */
            { /* Write error*/
                printf("\nChild write to FIFO failed"); 
                exit(1); 
            } 
            printf ("\nMessage sent."); 
        } 
        else 
        { 
        /* parent does a read */ 
            //printf ("Parent %ld is about to open FIFO %s\n", (long) getpid(), argv[1]); 
            if ((fd = open(argv[1], O_RDONLY | O_NONBLOCK)) == -1) /* Open for reading only*/
            { /* Open error*/
                perror("Parent cannot open FIFO"); 
                exit(1); 
            } 
            printf ("\nParent is about to read the message from %s\n", pipeName); 
            while ((wait(&status) == -1) && (errno == EINTR)); /* EINTR -> interrupted system call*/
                if (read(fd, buf, BUFSIZE) <=0) 
                /* success: number of bytes read, failure: -1, sets errno. 
                All reads are initiated from current position. Read nbyte bytes 
                from the open file associated with the file descriptor filedes 
                into the buffer referenced by buf. */
                { /* Read error*/
                    perror("Parent read from FIFO failed\n");
                    exit(1); 
                } 
            printf ("\nParent receives the message %s", buf); 










        // switch (fork())
        // { 
        //     case -1: /* Fork error*/
        //         perror ("Fork"); 
        //         exit(3); 
        //     case 0: /* In the child */ 
        //         close(f_des[0]); 
        //         if (write(f_des[1], inputMessage, strlen(inputMessage)) != -1)
        //         /* success: number of bytes written, 
        //         failure: -1, sets errno. Write nbyte bytes from the buffer 
        //         referenced by buf using the file descriptor pecified by filedes. */
        //         { 
        //             printf ("\nChild %ld is about to send the message [%s] to %s\n", (long)getpid(), inputMessage, pipeName);
        //             fflush(stdout); 
        //         } 
        //         else 
        //         { 
        //             perror ("Write"); 
        //             exit(5); 
        //         } 
        //         printf("\nMessage sent.\n");
        //         break; 
        //     default: /* In the parent */ 
        //         while ((wait(&status) == -1) && (errno == EINTR));
        //         printf("\nParent is about the read the message from %s\n", pipeName);
        //         close(f_des[1]); 
        //         if (read(f_des[0], message, BUFSIZ) != -1) 
        //         /* success: number of bytes read, failure: -1, sets errno. 
        //         All reads are initiated from current position. Read nbyte bytes 
        //         from the open file associated with the file descriptor filedes 
        //         into the buffer referenced by buf. */
        //        { 
        //             printf ("\nParent receives the message *%s* from child %ld\n", inputMessage, (long)getpid()); 
        //             fflush(stdout); 
        //         } 
        //         else 
        //         { 
        //             perror ("Read"); 
        //             exit(4);
        //         }  
        // }        
    } 

    else if (order == 1)
    {




        
        // switch (fork()) 
        // { 
        //     case -1: 
        //         perror ("Fork"); 
        //         exit(3); 
        //     case 0: /* In the child */ 
                
        //         close(f_des[1]); 
        //         if (read(f_des[0], message, BUFSIZ) != -1) 
        //         { 
        //            //printf ("Child %ld receives by child: *%s*\n", message); 
        //             fflush(stdout); 
        //         } 
        //         else 
        //         { 
        //             perror ("Read");
        //             exit(4);
        //         } 
        //         break; 
                
        //     default:  In the parent  
                
        //         close(f_des[0]); 
        //         if (write(f_des[1], inputMessage, strlen(inputMessage)) != -1)
        //         { 
        //             printf ("Parent is about to send the message [%s] to ", inputMessage);
        //             if (strcmp(argv[1], "n") == 0) 
        //                 printf("%s\n", argv[2]); 
        //             else
        //                 printf("FIFO\n");
        //             fflush(stdout); 
        //         } 
        //         else 
        //         { 
        //             perror ("Write"); 
        //             exit(5); 
        //         } 
        // }
    }
    exit(0); 
}
