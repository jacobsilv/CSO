#include <stdio.h>
#include <stdlib.h>


int
main (int argc, char **argv){
	if (argv[1]==NULL){
                printf("you for got to add a command line arg\n");
                exit(EXIT_SUCCESS);
        }


	// take in the command line arg and convert it to an int
	int n = atof(argv[1]);

	// run the main method that solves the problem
	solve(n);
	return 0;
}


/*
This will go up the the agrv given and figure out if the total sum of the ones that pass the divisor
prime checker.
*/
int
solve(int n){

	// iterater
	int j;
	// gather the sum of all the numbers whos divisors follow the prime test
        int total = 0;
        
	// iterate from zero to the number entered from the command line
        for (j=0; j <= n; j++){

		// add to the total/answer if the number passes the divisor/prime test
                if (divisors(j)==1){
                        //printf("%d \n",j);
                        total+= j; 
                }
        }

	// print the answer
        printf("%d\n", total);
	return 0;
}


/*
this will find the divisors of a number and then check to make sure all them pass 
the prime checker
*/
int
divisors(int num){

	int i, notPrime=0;

	// iterate from zero to the number you want to find the divisors of
	for(i=1;i<=num;i++){

		// see if the number is divisible by the iterator
		if(num%i==0){
			//printf("%d : ",i);
			//printf("%d \n",checkPrime(num, i));

			// if the number is a divisor then check to see it follows the prime checker and if not then return 0
			if (checkPrime(num, i)==0){
				return 0;
			}
		}
	}
	// all divisors follow the prime checker so this number is elligible to be added to the total
	return 1;
} 


/*
takes in the divisor and the number then plugs those into the function
and figures out if it is prime or not.
*/
int 
checkPrime(int num, int div){

	// make the number checked to be a prime a number that is plugged into the function
	int testPrime = (num/div)+div;
	int i;
	//int flag = 0;
 

	// start the iterator at 2 till have the number to be checked
	for(i=2;i<=testPrime/2;i++){

		// see if any of ther iterations can evenly divise into the number then it is not prime
		if(testPrime%i==0){
          		return 0;
      		}
  	}

	// nothing was able to divise into the testPrime number thus it is prime
	return 1;
}
