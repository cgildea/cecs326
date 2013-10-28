/*********************************************************************/
/* Cody Gildea 008933663 CECS 326                                    */
/* PROGRAM: lab3.c                                                   */
/* DESCRIPTION: This program demonstrates the various exec system    */ 
/* calls such as: execlp, execvp.				     */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void main(int argc, char *argv[])
{
	//if(argc > 1) 
	//{
		//Part 1 
		//This will run a cat file
		/*	
		execlp("/bin/cat","cat",argv[1],(char *)NULL);
		perror("exec failure");
		exit(1);
		*/
	
		//Part 2
		//This will run the execlp command with a ls argument
		/*
		execlp("/bin/ls","ls",argv[1],(char *)NULL);
		perror("exec failure");
		exit(1);
		*/

		//Part 3
		//This will run another file such as .c
		/*		
		execvp(argv[1],&argv[1]);
		perror("exec failure");
		exit(1);
		*/

		//Part 4
		//This will run a cat file named "yourfile.txt"
		
		static char *new_argv[] = {"lab2","5","5",(char *)0};
		execvp("/net/d2/u7/c/cs105a/ag/CECS326/lab2/lab2",new_argv);
		perror("exec failure");
		exit(1);
		
	//}
	printf("\nUsage: %s text_file\n",*argv);
	exit(1);

}
