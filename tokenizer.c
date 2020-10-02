#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//in

//isWord should check for isAlpha and isDigit, anything else is a delimiter.
//also account for all of the digits that were used for that word and return that number.
int isWord(char **in, int index, int count){

	printf("word: \"%c", in[index][count]);

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
	printf("\"");
	return count;
}

//known to be a number, now check for isDigit, if not check for special 'x', 'e' and '.' as well as octals.
int isNumber(char** in, int index, int count) {

	int isOctal = 0;
	int isHex = 0; 
	int isFloat = 0; 

	//if zero, check for octal 
	if(in[index][count] == '0') {
		isOctal = 1; 
	}
	//will hold the number until the token is finished. Not using a integer to account for leading zeros.
	//account for enough mem to hold the entire length of the input.
	char* temp =  malloc(sizeof(char)*strlen(in[index]));
	//keep track of how many numbers are in the string. 
	int tempIndex = 0; 
	temp[tempIndex] = in[index][count];
	tempIndex++; 
	
	count++; 
	//check IsDigit in loop, keep track of the previous number values. 	
	while(count < strlen(in[index])) {
		//not a number, either number ends or becomes float/hex 
		if(isdigit(in[index][count]) == 0) {

			//only floats can have contain a period, if its not a hex already, it is automatically a float since there is already a number behind it. 
			if(in[index][count] == '.') {

				//once something is set as Hex is cannot also be a float. Once it is a float is also cannot have a second period..
				if(isHex == 1 || isFloat > 0) {
					break; 
				}

				//update float/octal flags
				isFloat = 1;
			       	isOctal = 0; 
		
				temp[tempIndex] = in[index][count]; 
				tempIndex++;
				count++;
				continue; 
			}
		
			//if it is a float, it has possible e and - + chars, once an e is added change float to 2 to signifty that no more e's can be added.  
			if(isFloat == 1) {
				//check if the non-number is an e.
				if(in[index][count] == 'e' || in[index][count] == 'E') {
					//before adding the e, make sure it has valid chars after, numbers with possiblity of a + or _. 	
			
					//there is nothing after the e therefore not part of the float. 
					if(strlen(in[index]) == count+1) {
						break; 
					}

					//check for a sign and add it if there is one with a valid format
					if(strlen(in[index]) >= count+2) {
						puts("A");
						//check for sign
						if(in[index][count+1] == '+' || in[index][count+1] == '-') {
							//check for a number after the sign
							puts("b"); 
							if(isdigit(in[index][count+2])) {
								//add both the e and the sign
								temp[tempIndex] = in[index][count];
								temp[tempIndex+1] = in[index][count+1];
								tempIndex += 2;
								count += 2;
								
								isFloat = 2; 
								continue;
							}
						}	
					}

					//make sure the number after the e is a digit before adding, already checked bounds
					if(!isdigit(in[index][count+1])) {
						break;	
					}

					temp[tempIndex] = in[index][count]; 
					tempIndex++;
					count++;
					isFloat = 2;
					continue; 
				}	
			}

			//it is a letter between a-f and it is known to be a hex, then add it to temp. 
			if(isHex == 1) {
				//A-F
				if(in[index][count] <= 70 && in[index][count] >= 65) {
					temp[tempIndex] = in[index][count];
					tempIndex++;
					count++;
					continue;
				}

				//a-f
				if(in[index][count] <= 102 && in[index][count] >= 97) {   
					temp[tempIndex] = in[index][count];
					tempIndex++;
					count++;
					continue; 
				}	
			}

			//hex
			if(in[index][count] == 'x' || in[index][count] == 'X') {
				//in order for to be hex it must have 0x, it there was a zero then isOctal would be == 1. 
				if(isOctal == 1) {
					isHex = 1; 
					//it is no longer octal
					isOctal = 0;
				        //edit the string
					temp[tempIndex] = in[index][count]; 
					tempIndex++;
					count++;
					continue;
				}
				//it is not an octal, and the number is finished, with a word being next. 
					break;
			
			}

			//if not then it is a delimiter, break to print the decimal. 
			break;	
			
		}	
		//it is a number
		else{
			//check it is octal
			if((in[index][count] - 48) > 7) {
				isOctal = 0; 
			}
		}
		//must be a number, add it to temp and keep scanning
		temp[tempIndex] = in[index][count];
		tempIndex++;
		count++;

	}
	//check float flag
	if(isFloat == 1 || isFloat == 2) {
		printf("float: \"%s\"\n", temp);
		return count;
	}

	//check for hex flag
	if(isHex == 1) {
		printf("hexadecimal integer: \"%s\"\n", temp);
		return count; 
	}

	//check for octal flag 	
	if(isOctal == 1) {
		printf("octal integer: \"%s\"\n", temp);
		return count; 
	}

	//No more argument after, must be a decimal
	printf("decimal integer: \"%s\"\n", temp); 

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
