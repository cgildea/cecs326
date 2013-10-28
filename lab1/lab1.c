/*Cody Gildea 008933665
  CECS 326 lab1.c */

#include <stdio.h>
#include <stdlib.h>

int* randArray(int);

int main(int argc, char *argv[])//main
{
        //we need several ints to find the max, 		    //min, size of array
        //sum is used to calculate avg
        int min, max, num, sum;
        //random array declaration
        int *randA;

        //average is double to prevent truncation
        double avg;
        //To check if two strings are entered into 		   //the command line
        // file name and size of the random array: 		   //randA[num]
        if (argc !=2)
        {
                printf("\n Usage: Need filename and one argument\n", argv[0]);
                 exit(1);
        }
        //Assigns command line input to 'num'
        num = atoi(argv[1]);
        //For random function
        srand(time(NULL));
        //fill the random array
        randA = randArray(num);
        //fill 'max', 'min', 'ave', 'sum'
        max = randA[0];
        min = randA[0];
        avg = 0;
        sum = 0;
        int k;//for statement
        for(k=0;k<num;k++)//find 'max' and 'min'
        {
                if(randA[k] > max)
                        max = randA[k];
                if(randA[k] < min)
                        min = randA[k];
                sum = sum + randA[k];
        }
        //compute 'avg'
        avg = sum /(double)num;
        int j;//for statement
        for(j = 0; j < num; j++)//print randA
        {
                printf("%d ", randA[j]);
        }
        //print the 'max', 'min', 'avg'
        printf("\nThe min value is: %d \nThe max value is: %d \nThe average value is: %f\n\n",min, max, avg);
        //free randA
        free(randA);
        return 0;
}
//Create the random array
int* randArray(int n)
{
        int* h = (int *)malloc(n*sizeof(int));
        int i;
        for (i= 0; i<n; ++i)
                h[i]= rand()%201 - 100;
        return h;
}



