#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define CHANCES 6
#define WORD_SIZE 36
#define GUESS_SIZE 3


int main(int argc, char * argv[])
{
	FILE *fp;
	srand(time(NULL));
	char dictionary[WORD_SIZE];
	int ran;
	char *guess;

	guess = malloc(GUESS_SIZE);

	if (argc == 1)
	{
		//begins like normal
	}
	else if (argc == 2)
	{
		if (strncmp(argv[1], "-h", 10) == 0) //checks if the strings are equal
		{
			printf("Rules: \n");
		}
	}


	if (!(fp = fopen("words.txt", "r+")))
	{
		fprintf(stderr, "An error occured.\n");
		return 1;
	}
	else
	{
		int i;
		for (; fgets(dictionary, sizeof(dictionary), fp); i++)
		{
			;
		}

		ran = (rand() % i);
		rewind(fp);
	}

	for (int c = 0; c < ran; c++)
		fgets(dictionary, sizeof(dictionary), fp);

	printf("%s\n", dictionary);

	int word_length = (strlen(dictionary) - 1);

	while(1)
	{
		printf("What is your guess: ");
		fgets(guess, 6, stdin);

		printf("%d\n", word_length);

		if (guess[1] == '\n')
		{
			for (int y = 0; y < word_length; y++)
			{
				if (dictionary[y] == guess[0])
				{
					printf("In there\n");
				}
				else
				{
					printf("Ya\n");
				}
			}
		}
		else
		{
			printf("Not right\n");
			while(!strrchr(guess, '\n')){
				fgets(guess, 6, stdin);
			}	
		}

		printf("End loop\n");

	}

	fclose(fp);
	free(guess);
}
