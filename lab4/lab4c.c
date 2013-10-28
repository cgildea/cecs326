/*********************************************************************/
/* Cody Gildea 008933663 CECS 326                                    */
/* PROGRAM: lab4c.c                                                  */
/* DESCRIPTION: This program demonstrates more use of exec calls and */
/* the fork() function.                                              */
/*********************************************************************/
# include <stdio.h>
# include <unistd.h>
void main()
{
	//output message
        static char *mesg[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
        int display(char *), i;
	//display loop // Calls (int display)
        for (i=0; i<10; ++i)
                display(mesg[i]);
        sleep(2);//sleep for 2
}//end main
//display
int display(char *m)
{
        char err_msg[25];
        switch (fork())
        {
        case 0://execlp call to "haha/nofile"
                execlp("haha/nofile", "nofile", m, (char *) NULL);
                sprintf (err_msg, "%s Exec failure", m);
                perror(err_msg); exit(1);
        case -1: //fork call failed
                perror ("Fork failure"); return(2);
        default://bad input
                return(0);
        }
}//end display

