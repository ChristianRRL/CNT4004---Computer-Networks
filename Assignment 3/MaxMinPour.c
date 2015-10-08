//File: MaxMinPour
//Author: Christian Rodriguez
/*Instructions:
 Write a program that will implement max-min scheduling by simulating the 
 pouring process. The program should take as command line input the available 
 bandwidth and up to 10 requested data rates (this for up to 10 sources). The 
 bandwidth and data rates are all in integer increments of 1 Mb/s and the final 
 allocation is also to be an integer value (that is, no allocations of less than 
 1 Mb/s allowed). Here below is an execution of the program written for the 
 solution. You should give a screen shot showing the same inputs and outputs as 
 in the below screen shot. Also, run your program for the following two cases:
    * Available is 100 Mb/s - Source A requests 50 Mb/s, source B requests 70 Mb/s,
    and source C requests 10 Mb/s 
    And…
    * Available is 100 Mb/s - Source A requests 50 Mb/s, source B requests
    700 Mb/s, and source C requests 10 Mb/
    Submit also your source code.
*/

/* Reference(s): 
 http://www.tutorialspoint.com/cprogramming/c_command_line_arguments.htm
 https://msdn.microsoft.com/en-us/library/a1y7w461.aspx
 http://cboard.cprogramming.com/c-programming/134232-converting-command-line-char-*argv%5B%5D-int.html
 */
#include <stdio.h>

int main( int argc, char *argv[] )
{
    int available = atoi(argv[1]);
    int requestCount = argc - 2;
    //printf("available = %d\n", available);
    
    int bandwidthRequest[requestCount];
    int bandwidthCurrent[requestCount];
    
    //printf("Bandwidth(s): ");
    for (int i = 0; i < requestCount; i++)
    {
        bandwidthRequest[i] = atoi(argv[i+2]);
        bandwidthCurrent[i] = 0;
        //printf("%d ", bandwidthArr[i]);
    }
    
    int temp = 0;
//    printf("(1) requestCount: %d\n", requestCount);
//    printf("(2) temp: %d\n", temp);
    while ((available > 0) && (temp < 3))
    {
        temp = 0;

        for (int i = 0; i < requestCount; i++)
        {
            if (bandwidthCurrent[i] < bandwidthRequest[i])
            {
                bandwidthCurrent[i] += 1;
                available--;
            }
            else
            {
                temp++;
            }
            if (available <= 0) {
                break;
            }
        }
//        printf("(3) temp: %d\t\trequestCount: %d\n", temp, requestCount);
//        printf("(4) available: %d\t\t'0'\n", available);
//        printf("(5)temp < requestCount: %d\n", (temp < requestCount));
//        printf("(6)available > 0: %d\n", (available > 0));
//        
////        getchar();
    }
    
    printf("Allocated bandwidth = ");
    for (int i = 0; i < requestCount; i++) {
        printf("%d ", bandwidthCurrent[i]);
    }
    
    printf("\nAvailable bandwidth after allocations = %d", available);
    
    
//    for (int i = available; i > available; i--)
//    {
//        
//    }

    printf("\n");
}