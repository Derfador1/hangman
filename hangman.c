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


	char * word = dictionary;
	int correct_guess = 0;
	int number_guesses = 0;

	size_t size = sizeof(word);

	char * secret_array;

	secret_array = malloc(size);

	for (int unsigned f = 0; f < size; f++)
	{
		secret_array[f] = '_';
	}

	while(1)
	{
		printf("What is your guess: ");
		fgets(guess, 6, stdin);

		//printf("%d\n", word_length);
		printf("%s\n", word);
		if (guess[1] == '\n')
		{
			for (int unsigned y = 0; y < size; y++)
			{
				if (dictionary[y] == guess[0])
				{
					secret_array[y] = guess[0];
					correct_guess++;
				}
				else
				{
				}
			}
			number_guesses++;
			printf("Total guesses is : %d\n", number_guesses);
			printf("%s\n", secret_array);
		}
		else
		{
			printf("Not right\n");
			while(!strrchr(guess, '\n')){
				fgets(guess, 6, stdin);
			}	
		}


	}

	fclose(fp);
	free(guess);
	free(secret_array);
}
