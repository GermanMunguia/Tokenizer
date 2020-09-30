#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//in

//isWord should check for isAlpha and isDigit, anything else is a delimiter.
//also account for all of the digits that were used for that word and return that number.
int isWord(char **in, int index, int count){

	printf("word: %c", in[index][count]);

	//printf("strlen > count:  %ld\n", strlen(in[index]));

	count++;
	//int tokenLen = 0;
	while (count < strlen(in[index]))
	{
		//since it is known to be a word, any letter or number after it is part of the word.
		if (isalpha(in[index][count]) || isdigit(in[index][count]))
		{
			printf("%c", in[index][count]);
			count++;
		}

		else
		{
			break;
		}
	}

	return count;
}

//known to be a number, now check for isDigit, if not check for special 'x', 'e' and '.' as well as octals.
int isNumber(char** in, int index, int count) {


	//if zero, check for octal 
	if(in[index][count] == '0') {
		printf("potential for octal\n");
	}
	//will hold the number until the token is finished. Not using a integer to account for leading zeros.
	//account for enough mem to hold the entire length of the input.
	char* temp =  malloc(sizeof(char)*strlen(in[index]));
	//keep track of how many numbers are in the string. 
	int tempIndex = 0; 
	temp[tempIndex] = in[index][count];
	tempIndex++; 
	//printf("temp: %s\n", temp);
	
	count++; 
	//check IsDigit in loop, keep track of the previous number values. 	
	while(count < strlen(in[index])) {
		//not a number, either number ends to becomes float/hex 
		if(isdigit(in[index][count]) == 0) {
			//float
			if(in[index][count] == '.') {
				//do something
				break;
				//return count;	
			}
			//float
			if(in[index][count] == 'e' || in[index][count] == 'E') {
				//do something
				break;
				//return count;
			}
			//hex
			if(in[index][count] == 'x' || in[index][count] == 'X') {
				//do something
				break; 
				//return count;
			}
			//if not then it is a delimiter, break to print the decimal. 
			break;	
			
		}
		//must be a number, add it to temp and keep scanning
		temp[tempIndex] = in[index][count];
		tempIndex++;
		count++; 

	}
	
	//No more argument after, must be a decimal
	printf("Decimal: \"%s\"\n", temp); 

	return count;
}


int main(int argc, char **argv){

	//make sure to check for an appropriate number of arguments

	printf("\n\nargc: %d\n", argc);
	printf("arguments: %d\n", argc - 1);

	for (int i = 1; i < argc; i++)
	{
		printf(" %s     len: %ld \n\n\n", argv[i], strlen(argv[i]));
	}

	char **in = argv;

	//Check for more arguments as quotes are not guaranteed. 
	for (int i = 1; i < argc; i++)
	{

		int count = 0;
		while (count < strlen(in[i]))
		{

			//check for any delimiter that is not part of any token type.
			//this includes white spaces, newlines...

			//if the first index is a letter, it is a word.
			if (isalpha(in[i][count]) != 0)
			{
				//printf("word: %c\n", in[i][count]);
				count = isWord(in, i, count);
				printf("\n");
				continue;
			}

			//if the first index is a digit, it is some type of number.
			if(isdigit(in[i][count]) != 0) {
				count = isNumber(in, i, count);
				continue;
			}

			//if its not a number or letter, then all types of symbols have to be checked.

			printf("undefined: %c\n", in[i][count]);
			count++;
		}
		//if the for loop triggers a second time it is automatically a new delimiter
	}
}
