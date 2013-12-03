/* Named pipe pipe1.c */ 
/* Usage: pipe1 pipename. Child writes a message to parent */ 
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
 mode_t fifo_mode = S_IRUSR | S_IWUSR; int fd, status, child; char buf[BUFSIZE]; unsigned strsize; 
 
 if (argc !=2) { printf ("\n Usage: %s pipename\n", argv[0]); exit(1); } 
 /* generate a named pipe with r/w for user */ 
 if ((mkfifo(argv[1],fifo_mode) == -1) && (errno != EEXIST)) { perror ("Pipe"); exit(1); } 
 if (( child = fork()) == -1) { perror ("Fork"); exit(1); } 
 else if (child == 0){ printf ("\n Child %ld is about to open FIFO %s\n", (long)getpid(), argv[1]); 
 if ((fd = open(argv[1], O_WRONLY)) == -1) {perror("Child cannot open FIFO"); exit(1);} 
 /* In the child */ 
 sprintf (buf, "This was written by child %ld\n", (long)getpid()); strsize = strlen(buf) + 1; 
 if (write(fd, buf, strsize) != strsize) { printf("Child write to FIFO failed\n"); exit(1); } 
 printf ("Child %ld is done\n", (long)getpid()); 
 } else { /* parent does a read */ 
 printf ("Parent %ld is about to open FIFO %s\n", (long) getpid(), argv[1]); 
 if ((fd = open(argv[1], O_RDONLY | O_NONBLOCK)) == -1) { perror("Parent cannot open FIFO"); 
exit(1); } 
 printf ("Parent is about to read\n", (long)getpid()); 
 while ((wait(&status) == -1) && (errno == EINTR)); 
 if (read(fd, buf, BUFSIZE) <=0) { perror("Parent read from FIFO failed\n");exit(1); } 
 printf ("Parent %ld received: %s\n", (long)getpid(), buf); 
 } 
 exit(0); 
}
