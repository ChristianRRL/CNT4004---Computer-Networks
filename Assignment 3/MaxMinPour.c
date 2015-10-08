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
#include <stdlib.h>

int main( int argc, char *argv[] )
{
    int requestCount;
    
    // Handle different argc inputs
    if( argc == 1 )
    {
        printf("Available bandwidth expected.\n");
        printf("Up to ten bandwidth requests expected.\n");
        return 0;
    }
    else if ( argc == 2 )
    {
        printf("Available bandwidth supplied is %s.\n", argv[1]);
        printf("Up to ten bandwidth requests expected.\n");
        return 0;
    }
    else if ( argc > 12 )
    {
        printf("Over ten bandwidth requests supplied.\n");
        printf("Only first 10 to be used.\n");
        requestCount = 10;
    }
    else
    {
        requestCount = argc - 2;
    }
    
    
    int availableRequest = atoi(argv[1]);   // Convert argv[1] string to int
    int bandwidthRequest[requestCount];
    int bandwidthCurrent[requestCount];
    
    // Fill in current bandwidth array and requested bandwidth array
    for (int i = 0; i < requestCount; i++)
    {
        bandwidthRequest[i] = atoi(argv[i+2]);
        bandwidthCurrent[i] = 0;
    }
    
    
    int filledCount = 0;
    
    // Loop until either available bandwidth reaches 0 or all requests are filled
    while ((availableRequest > 0) && (filledCount < requestCount))
    {
        filledCount = 0;
        
        // Fill in each bandwidth request appropriately
        for (int i = 0; i < requestCount; i++)
        {
            // Handle different empty/filled bandwidth request cases
            if (bandwidthCurrent[i] < bandwidthRequest[i])
            {
                bandwidthCurrent[i] += 1;
                availableRequest--;
            }
            else
            {
                filledCount++;
            }
            
            // Handle running out of available bandwidth
            if (availableRequest <= 0) {
                break;
            }
        }
    }
    
    // Print each allocated bandwidth
    printf("Allocated bandwidth = ");
    for (int i = 0; i < requestCount; i++) {
        printf("%d ", bandwidthCurrent[i]);
    }
    
    // Print remaining bandwidth
    printf("\nAvailable bandwidth after allocations = %d", availableRequest);

    printf("\n");
    
    return 0;
}