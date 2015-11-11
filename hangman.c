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
	int correct_guesses = 0;
	int number_guesses = 0;
	int wrong_guesses = 0;
	int tracker = 1;
	int winner = 1;

	size_t size = sizeof(word);

	char * secret_array;
	
	word = malloc(size);
	secret_array = malloc(size);

	for (int unsigned f = 0; f < size; f++)
	{
		secret_array[f] = '_';
	}

	while(1)
	{
		printf("What is your guess: ");
		fgets(guess, 6, stdin);

		if (guess[1] == '\n')
		{
			for (int unsigned y = 0; y <= size + 1; ++y)
			{
				if (dictionary[y] == guess[0])
				{
					secret_array[y] = guess[0];
					correct_guesses++;
					tracker = 0;
				}

			}

			if (tracker == 1)
			{
				printf("That was not in the word\n");
				wrong_guesses++;
			}

			number_guesses++;
			printf("%s\n", dictionary);
			printf("Total guesses is : %d\n", number_guesses);
			printf("%s\n", secret_array);

			printf("Correct guesses are : %d\n", correct_guesses);
			printf("Wrong guesses are : %d\n", wrong_guesses);
			tracker = 1;

			for (int unsigned c = 0; c <= size; ++c)
			{
				if (secret_array[c] == '_')
				{
					winner = 0;
					break;	
				}
				else
					winner = 1;	
			}

			if (winner == 1)
			{
				printf("you win\n");
				break;
			}
			else if (wrong_guesses == CHANCES)
			{
				printf("You lose\n");
				break;
			}
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
	free(word);
}
