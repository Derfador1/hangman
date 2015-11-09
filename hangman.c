#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define CHANCES 5
#define WORDS 5

int main(int argc, char * argv[])
{

	srand(time(NULL));
	int i;


	if (argc == 1)
	{
		//begins like normal
	}
	else if (argc == 2)
	{
		if (strncmp(argv[1], "-h", 10) == 0) //checks if the strings are equal
		{
			printf("Rule: \n");
		}
	}

	char *dictionary[] = {"WORD", "COW", "CHEESE", "POOP", "FALSE"};

	for (int c = 0; c < 5; c++)
		printf("%s\n", dictionary[c]);

	i = (rand() % WORDS);

	char * word = dictionary[i];
	size_t length = strlen(word);
	for (unsigned int y = 0; y < length; y++)
	{
		printf("_ ");
	}
	printf("\nSize : %zd\n", length);
	printf("%s\n", word);

}
