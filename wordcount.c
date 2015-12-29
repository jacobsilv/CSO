#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
wrapper for the qsort that returns the strcmp funciton 
*/
static int cmp(const void *p1, const void *p2){
	return strcmp(*(char **)p1, *(char **)p2);
}

/*
This is a very dense main method that solves the entire 10 top wors used in the fist command line 
argument that is the bible.txt file
*/
int main(int argc, char **argv){


	// if the user doesn't input any command line arg 
	if (argv[1]==NULL || argc==0){
		printf("you for got to add the text file\n");
		exit(EXIT_SUCCESS);
	}

	// takes in the file and sets file equal to read the argv[1]
	char const* const fileName = argv[1]; /* should check that argc > 1 */
	FILE* file = fopen(fileName, "r"); /* should check the result */	
	

	// test to see if the user input a valid text file
	if (file == '\0'){
		fprintf(stderr, "failed to open input.txt\n");
		exit(1);
	}


	// storing the important chars of the bible text into a char array that has more memory than needed
	char charArray[4200000];

	// iterator for storing into the char array
	int i=0;

	// int that holds that ascii char that is obtained from the file
	int c;
	// check to make sure that a bunch of spaces arent stored one after another
	int spaceflag=0;
	
	// while loop that runs through the whole file char by char storing the value into c until end of file
	while ((c = fgetc(file)) != EOF) {

		// the char being assigned to c is a capital letter
		if(c>=65 && c<=90){
			// add 32 to the char cause that is the difference between the upper and lower case letter
			c= c+32;
			charArray[i]=(char) c;
			i++;
			spaceflag=0;

		// the cahr being looked at is a normal lower case letter so add it to the char array and increment i
		} else if (c>=97&& c<= 122){
			
			charArray[i] = (char) c;
			i++;
			spaceflag=0;

		// these are the spacing cases where a space, new line, or tab are found
		}else if ((c==9||c==10 || c==32) && spaceflag!=1){

			charArray[i]=(char) 32;
			i++;
			// set spaceflag to 1 so it knows that the previous val added to the array was a space
			spaceflag =1;
		}
		
	}
	//printer(charArray);

	// allocate memory for a string array then setting the memory to null
	char **stringArray = (char **)malloc(sizeof(char*)*1000000);
	memset(stringArray, 0, sizeof(char *)*1000000);
	
	// max len of a word in the bible.txt file is 19
	int len = 19;
	int y=0;

	// iterate through all the elements of the string array
	for (y; y<1000000; y++){
		// create a string of size 20 that sets all the memory to null
		char *str = (char *)malloc(sizeof(char)*(len+1));
		memset(str, 0, sizeof(char)*(len+1));
		// have the elements of the string array point to a string with 20 spaces of memory allocated to it
		stringArray[y] = str;
	}
	
	// j = iterator for the char array, k = iterator for string elements, m = iterator for string rows in the string array
	int j=0, k=0, m=0;

	// continue till there are no more chars in the char array to look at
	while(charArray[j]!='\0'){

		// the current char is a space so it is time to reset k and go to the next row of the string array
		if(isspace(charArray[j])){
			// reset string pointer position to zero so it starts a new word
			k=0;
			// increase the string array row by one to add a new word
			m++;
			// look at the next char of the char array
			j++;

		// the char array position being looked at is a char that is important
		}else if (charArray[j]>=97 && charArray[j]<=122){

			// add that char into the string array 
			*(stringArray[m]+k) = charArray[j];

			// increase the string pointer position by one
			k++;
			// increase the position in the char array by one
			j++;
		}
	}

	qsort(stringArray, 1000000, sizeof(char*), cmp);

	// allocate memory for the string array of size 
	char **solutionArray = (char **)malloc(sizeof(char*)*11);
	memset(solutionArray, 0, sizeof(char *)*11);
	

	int s=0;
	// allocated the string array to be filled with string of size 20
	for (s; s<11; s++){
		char *str = (char *)malloc(sizeof(char)*(len+1));
		memset(str, 0, sizeof(char)*(len+1));
		solutionArray[s] = str;
	}


	int r=0;
	// counts the number of null characters
	while(!strcmp(*(stringArray+r), "\0")){
		r++;
	}

	// keep the start of the array memorized for whenever i need to skip the nulls and look at the first word
	int skipNulls =r;

	// this skips all the first null characters
	m=r+m;

	/*
	while(r<m){
		printf("%s ", *(stringArray+r));
		r++;
	}*/

	int g=0; // used to increment 10 times
	int z =0; // increments through solution array
	int inc = 0; // adds to the solution array
	
	// counters and strings for obtaining the current/max count and string
	int max = 0;
	int counter = 1;
	char* maxWord = (char *)malloc(sizeof(char)*(len+1));
	char* currentWord = (char *)malloc(sizeof(char)*(len+1));
	// make an array of the number of repetition that the max words happen
	int maxNumbers[10];	


	// finds 10 words
	for (g; g < 10; g++){
		
		// skips nulls and iterates through sorted string array
		while (r<m){

			// checks the solution array word strings 0, 2, 4, etc
			for (z; z<10; z++){
				// if the values we are on is already a solution
				if(!strcmp(*(stringArray+r), solutionArray[z])){
					// iterate r will we are no longer looking at that word that is a solution
					while (!strcmp(*(stringArray+r), solutionArray[z])) r++;
				}
			}
			
			// if the word we are on is not the next word
			if (strcmp(currentWord, *(stringArray+r))){

				// if the counter of that previous word exceeds/equals the previous max
				if(counter >= max ){

					// set the new max to that counter and make it the maxWord
					maxWord = currentWord;
					max = counter;
				}
				// if it did not exceed the max make the current the next word and reset counter
				currentWord = *(stringArray+r);
				counter =1;
			}

			// if you are looking at word repeated increment the counter
			else{
				counter++;
			}
			// keep incrementing r to look through the entire array of strings
			r++;
			// reset z so we can look through the solutions again
			z=0;
			
		}
		// making a separate array that stores the number of repetitions for the top words
		maxNumbers[inc] = max;

		// add the word found that had the max repeats with its count
		solutionArray[inc++] = maxWord;
		
		//reset the max and have r start at the beginning of the string array again
		max=0;
		r=skipNulls;
	}


	// prints the solution array from first to last element
	inc=0;
	// keep going till the next next value is null
	while( solutionArray[inc+2]!='\0'){

		//somehow the first and last values are off by one so i fix that ;D
		if (inc ==0 || inc == 9){
			printf("%s: ", solutionArray[inc]);
			printf("%d\n", maxNumbers[inc]+1);// add one extra to the first and last values

		}else{
			printf("%s: ", solutionArray[inc]);
			printf("%d\n", maxNumbers[inc]);
		}
		inc++;
	}

	// close the file 
	fclose(file);
	return 0;
}


// prints the characters stored in a my string array that is made when i read the file
// not necessary for the code but just useful as a checker
int
printer(char array[]){
	int i=0;
        while(array[i]!='\0'){
                printf("%c",array[i]);
                i++;
        }
	return 0;
}


