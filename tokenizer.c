#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//in

//isWord should check for isAlpha and isDigit, anything else is a delimiter.
//also account for all of the digits that were used for that word and return that number.
int isWord(char **in, int index, int count)
{

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

int main(int argc, char **argv)
{

	//make sure to check for an appropriate number of arguments

	printf("\n\nargc: %d\n", argc);
	printf("arguments: %d\n", argc - 1);

	for (int i = 1; i < argc; i++)
	{
		printf(" %s     len: %ld \n\n\n", argv[i], strlen(argv[i]));
	}

	char **in = argv;

	//incase that quations are not guaraanteed
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

			//if its not a number or letter, then all types of symbols have to be checked.

			printf("undefined: %c\n", in[i][count]);
			count++;
		}
		//if the for loop triggers a second time it is automatically a new delimiter
	}
}
