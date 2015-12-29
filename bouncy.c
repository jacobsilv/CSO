
#include <stdio.h>
#include <stdlib.h>


int
main (int argc, char **argv){

	// make sure there is a command line arg
	if (argv[1]==NULL){
                printf("you for got to add the percentage\n");
                exit(EXIT_SUCCESS);
        }

	//using atof because im am assume the user is not an idiot and will put in the proper input
	double percent = atof(argv[1]);
	checker(percent);
	return 0;
}

/*
the general checker that iterates till there are enough bouncy numbers to 
match the percentage given through the command line arg
*/
int
checker(double percent){
	// iterator
	int i=0;
	//counter the number of bouncy numbers found
        int counter=0;
	// initialize the percentage of bouncy numbers found compared to the number of iterations
        double p=0.00000000;

	// continue iterating till the percentage matches
        while(p != percent ){

		// this means that a bouncy number has been found
                if (!increasing(i)&&!decreasing(i)){
                        //printf("%d ", i);
			// add one to the number of bouncy numbers found
                        counter++;
			// figure out the the percentage of bouncy numbers compared to total numbers iterated
                        p = (double) counter/ (double) i;
			// multiple it by 100 so it is not a decimal but 
			//it can match an int that is passed through the command line
                        p = p*100.00;
                        //printf("%f\n", p);    
                }

		// the percentage of bouncy numbers matches or is greater than the percentage given from the command line
                if (p>=percent){

			//print the number where the percentage was found
                        printf("%d\n", i);
			// return to end the iteration
                        return 0;
                }
                i++;
        }
	return 0;

}

/*
checks to see if the value is increasing from right to left

*/
int 
increasing(int val){

	int previous = 0;
	int current;

	// until the value is zero
	while (val !=0){

		// find the farthest left value
		current = val %10;

		// get rid of the farthest left number
		val = val/10;

		// the second the values from right to left is not increasing return showing it is not increasing
		if (!(current >= previous)){
			return 0;
		}

		// make the prvious value the current and then set current to the next remainder
		previous = current;
	}
	// if it was increasing then it will return 1
	return 1;
}

/*
Check to see if the number input is decreasing from right to left
*/
int 
decreasing(int val){

	// this is 1 more than the max number the mod of the val can be
	int previous = 10;
	int current;

	// keep modding and dividing by ten till the number is zero
	while (val !=0){
		// look at the farthest right value of the val and set it to current to check for bounciness
		current = val %10;
		// have val hold all values besides the farthest right integer
		val = val/10;

		// check to see if the previous value was greater than or equal to the current one
		if (!(current <= previous)){

			// if it wasnt then this number is not decreasing from right to left
			return 0;
		}
		// make the previous value current so then it can be check to the next current calc from mod 10
		previous = current;
	}
	// all values from right to left were decreasing so return one that it is decreasing
	return 1;

}
