#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//isWord should check for isAlpha and isDigit, anything else is a delimiter.
//also account for all of the digits that were used for that word and return that number.
int isWord(char **in, int index, int count){
	//create a temporary string to hold each character in a word to later print. 
	char* temp =  malloc(sizeof(char)*(strlen(in[index])));
	int tempIndex = 0; 
	temp[tempIndex] = in[index][count]; 
	count++;
	tempIndex++;

	while (count < strlen(in[index]))
	{
		//since it is known to be a word, any letter or number after it is part of the word.
		if (isalpha(in[index][count]) || isdigit(in[index][count]))
		{
			temp[tempIndex] = in[index][count]; 
			tempIndex++;
			count++;
			continue; 
		}
			break;
	}

	//test the word for sizeof operator
	if(strcmp(temp, "sizeof") == 0) {
		printf("sizeof: \"%s\"\n", temp);
		return count;
	}

	printf("word: \"%s\"\n", temp);
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
	char* temp =  malloc(sizeof(char)*(strlen(in[index])));
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

				//make sure there is a number after the period in order for it to be a valid float.
				if(strlen(in[index]) == count+1) {
					break;
				}
				if(!isdigit(in[index][count+1])) {
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
						//check for sign
						if(in[index][count+1] == '+' || in[index][count+1] == '-') {
							//check for a number after the sign
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
				//in order for to be hex it must have 0x, if there was a zero then isOctal would be == 1. 
				if(isOctal == 1 && tempIndex == 1) {
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

	//No more arguments after, must be a decimal
	printf("decimal integer: \"%s\"\n", temp); 

	return count;
}

//test for each operator, check for out of bounds when testing operators longer than 1 char. 
int isOperator(char **in, int index, int count) {

	//check for + and all operators that being with it
	if(in[index][count] == '+') {
		//could be longer, += or ++, check for out of bounds first 
		if(strlen(in[index]) >= count +1) {
			//++ is longer therefore its printed over +
			if(in[index][count+1] == '+') {
				printf("increment: \"++\"\n");
				count += 2; 
				return count; 
			}
			//+=
			if(in[index][count+1] == '=') {
				printf("plus equals: \"+=\"\n");
				count += 2; 
				return count; 
			}
		}
		//if not then it must be just +
		printf("addition: \"+\"\n");
		count++; 
		return count; 
	}

	//check for < and all operators that being with it
	if(in[index][count] == '<') {
		//could be longer up the 3,  << <= <<= 
		if(strlen(in[index]) >= count +1) {
			//<< is longer than <
			if(in[index][count+1] == '<') {
				//check if there is enough space
				if(strlen(in[index]) >= count+2) {
					//<<= is longer than <<
					if(in[index][count+2] == '=') {
						printf("shift left equals: \"<<=\"\n");
						count += 3; 
						return count; 		
					}
				}
				
				printf("shift left: \"<<\"\n");
				count += 2; 
				return count; 
			}
			//<=
			if(in[index][count+1] == '=') {
				printf("less that or equal test: \"<=\"\n");
				count += 2; 
				return count; 
			}
		}
		//if not then it must be just <
		printf("less than test: \"<\"\n");
		count++; 
		return count; 
	}

	//check for > and all operators that being with it
	if(in[index][count] == '>') {
		//could be longer up the 3,  >> >= >>= 
		if(strlen(in[index]) >= count +1) {
			//<< is longer than <
			if(in[index][count+1] == '>') {
				//check if there is enough space
				if(strlen(in[index]) >= count+2) {
					//>>= is longer than >>
					if(in[index][count+2] == '=') {
						printf("shift right equals: \">>=\"\n");
						count += 3; 
						return count; 		
					}
				}
				
				printf("shift right: \">>\"\n");
				count += 2; 
				return count; 
			}
			//>=
			if(in[index][count+1] == '=') {
				printf("greater that or equal test: \">=\"\n");
				count += 2; 
				return count; 
			}
		}
		//if not then it must be just >
		printf("greater than test: \">\"\n");
		count++; 
		return count; 
	}


		//check for - and all operators that being with it
		if (in[index][count] == '-') {
			//could be longer, -= or --, check for out of bounds first 
			if (strlen(in[index]) >= count + 1) {
				//-- is longer therefore its printed over -
				if (in[index][count + 1] == '-') {
					printf("decrement: \"--\"\n");
					count += 2;
					return count;
				}
				//-=
				if (in[index][count + 1] == '=') {
					printf("minus equals: \"-=\"\n");
					count += 2;
					return count;
				}
				//->
				if (in[index][count + 1] == '>') {
					printf("structure pointer: \"->\"\n");
					count += 2;
					return count;
				}
			}
			//if not then it must be just -
			printf("minus/subtract operator: \"-\"\n");
			count++;
			return count;


		}
		//check for & and all operators that being with it
		if (in[index][count] == '&') {
			//could be longer, &= or &&, check for out of bounds first 
			if (strlen(in[index]) >= count + 1) {
				//&& is longer therefore its printed over &
				if (in[index][count + 1] == '&') {
					printf("logical AND: \"&&\"\n");
					count += 2;
					return count;
				}
				//&=
				if (in[index][count + 1] == '=') {
					printf("bitwise AND equals: \"&=\"\n");
					count += 2;
					return count;
				}
			}
			//if not then it must be just &
			printf("AND/address operator: \"&\"\n");
			count++;
			return count;
		}

		//check for | and all operators that being with it
		if (in[index][count] == '|') {
			//could be longer, |= or ||, check for out of bounds first 
			if (strlen(in[index]) >= count + 1) {
				//|| is longer therefore its printed over |
				if (in[index][count + 1] == '|') {
					printf("logical OR: \"||\"\n");
					count += 2;
					return count;
				}
				//|=
				if (in[index][count + 1] == '=') {
					printf("bitwise OR equals: \"|=\"\n");
					count += 2;
					return count;
				}
			}
			//if not then it must be just |
			printf("bitwise OR: \"|\"\n");
			count++;
			return count;
		}

		//check for = and all operators that being with it
		if (in[index][count] == '=') {
			//could be longer (==), check for out of bounds first 
			if (strlen(in[index]) >= count + 1) {
				//== is longer therefore its printed over =
				if (in[index][count + 1] == '=') {
					printf("equality test: \"==\"\n");
					count += 2;
					return count;
				}
			}
			//if not then it must be just =
			printf("assignment: \"=\"\n");
			count++;
			return count;
		}

		//check for ^ and all operators that being with it
		if (in[index][count] == '^') {
			//could be longer (^=), check for out of bounds first 
			if (strlen(in[index]) >= count + 1) {
				//^= is longer therefore its printed over ^
				if (in[index][count + 1] == '=') {
					printf("bitwise XOR equals: \"^=\"\n");
					count += 2;
					return count;
				}
			}
			//if not then it must be just ^
			printf("bitwise XOR: \"^\"\n");
			count++;
			return count;
		}
		//check for * and all operators that being with it
		if (in[index][count] == '*') {
			//could be longer (*=), check for out of bounds first 
			if (strlen(in[index]) >= count + 1) {
				//*= is longer therefore its printed over *
				if (in[index][count + 1] == '=') {
					printf("times equals: \"*=\"\n");
					count += 2;
					return count;
				}
			}
			//if not then it must be just *
			printf("multiply/dereference operator: \"*\"\n");
			count++;
			return count;
		}
		//check for / and all operators that being with it
		if (in[index][count] == '/') {
			//could be longer (/=), check for out of bounds first 
			if (strlen(in[index]) >= count + 1) {
				// /= is longer therefore its printed over /
				if (in[index][count + 1] == '=') {
					printf("divide equals: \"/=\"\n");
					count += 2;
					return count;
				}
			}
			//if not then it must be just /
			printf("division: \"/\"\n");
			count++;
			return count;
		}

		//check for % operator that being with it
		if (in[index][count] == '%') {
			// check for out of bounds first 
			if (strlen(in[index]) >= count + 1) {
				//%= is printed
				if (in[index][count + 1] == '=') {
					printf("mod equals: \"%%=\"\n");
					count += 2;
					return count;
				}
			}

		}
		//check for ! and all operators that being with it
		if (in[index][count] == '!') {
			//could be longer (!=), check for out of bounds first 
			if (strlen(in[index]) >= count + 1) {
				//!= is longer therefore its printed over !
				if (in[index][count + 1] == '=') {
					printf("inequality test: \"!=\"\n");
					count += 2;
					return count;
				}
			}
			//if not then it must be just !
			printf("negate: \"!\"\n");
			count++;
			return count;
		}

		//check for any other single character operator
		if (in[index][count] == '(') {
			printf("left parenthesis: \"(\"\n");
			count++;
			return count;
		}
		if (in[index][count] == ')') {
			printf("right parenthesis: \")\"\n");
			count++;
			return count;
		}
		if (in[index][count] == '[') {
			printf("left bracket: \"[\"\n");
			count++;
			return count;
		}
		if (in[index][count] == ']') {
			printf("right bracket: \"]\"\n");
			count++;
			return count;
		}
		if (in[index][count] == '.') {
			printf("structure member: \".\"\n");
			count++;
			return count;
		}
		if (in[index][count] == ',') {
			printf("comma: \",\"\n");
			count++;
			return count;
		}
		if (in[index][count] == '~') {
			printf("1s complement: \"~\"\n");
			count++;
			return count;
		}
		if (in[index][count] == ':') {
			printf("conditional false: \":\"\n");
			count++;
			return count;
		}
		if (in[index][count] == '?') {
			printf("conditional true: \"?\"\n");
			count++;
			return count;
		}

	//if not found, then it is not in RefCard and it is ignored. 
	count++;
	return count; 
}


int main(int argc, char **argv){

//	printf("\n\nargc: %d\n", argc);
//	printf("arguments: %d\n", argc - 1);
//	for (int i = 1; i < argc; i++)
//	{
//		printf(" %s     len: %ld \n\n\n", argv[i], strlen(argv[i]));
//	}

	char **in = argv;

	//Check for more arguments as quotes are not guaranteed. 
	for (int i = 1; i < argc; i++)
	{

		int count = 0;
		while (count < strlen(in[i]))
		{

			//check for any delimiter that is not part of any token type.
			//this includes white spaces, newlines...
			if(isspace(in[i][count]) != 0) {
				count++;
				continue; 	
			}

			//if the first index is a letter, it is a word.
			if (isalpha(in[i][count]) != 0)
			{
				count = isWord(in, i, count);
				continue;
			}

			//if the first index is a digit, it is some type of number.
			if(isdigit(in[i][count]) != 0) {
				count = isNumber(in, i, count);
				continue;
			}

			//if its not a number or letter, then all types of symbols have to be checked. If its not in RefCard then it is tossed. 
			count = isOperator(in,i,count); 

		}
		//if the for loop triggers a second time it is automatically a new delimiter
	}
}
