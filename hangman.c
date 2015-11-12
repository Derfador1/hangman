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

			for (int c = 0; c < ran; c++)
				fgets(dictionary, sizeof(dictionary), fp);
		}
	}
	else if (argc == 2)
	{
		if (strncmp(argv[1], "-h", 10) == 0) //checks if the strings are equal
		{
			printf("Rules:\n");
		}
		else
		{
			if (!(fp = fopen(argv[1], "r+")))
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

				for (int c = 0; c < ran; c++)
					fgets(dictionary, sizeof(dictionary), fp);
			}
			
		}
	}
			
	char * word = dictionary;
	int unsigned g = 0;
	int wrong_guesses = 0;
	//int correct_guesses var
	int tracker = 1;
	int winner = 1;
	int already = 1;
	size_t size = sizeof(word);
	char * secret_array;
	
	word = malloc(size);
	secret_array = malloc(size);

	for (g = 0; g < size; g++)
	{
		secret_array[g] = '_';
	}

	while(1)
	{
		printf("What is your guess: ");
		fgets(guess, 6, stdin);

		if (*guess >= 'a' && *guess <= 'z')
		{
			*guess = ('A' + *guess - 'a');
		}


		for (g = 0; g < size; ++g)
		{
			if (secret_array[g] == guess[0])
			{
				printf("Already in guess\n\n");
				already = 0;
			}
		}

		if (guess[1] == '\n')
		{
			for (g = 0; g < size; ++g)
			{
				if (already == 1)
				{
					if (dictionary[g] == guess[0])
					{
						secret_array[g] = guess[0];
						//correct_guesses++ counter
						tracker = 0;
					}
				}
				else
				{
					if (dictionary[g] == guess[0])
					{
						tracker = 0;
					}
				}
			}

			if (tracker == 1)
			{
				printf("That was not in the word\n\n");
				wrong_guesses++;
			}


			printf("Size of word is : %zd\n\n", size);
			printf("%s\n", secret_array);

			printf("Wrong guesses are : %d\n", wrong_guesses);
			tracker = 1;
			already = 1;
			//printf("\n%s\n", hung[0]);

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
				printf("You win\n");
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

	//open file and write stats to it

	fclose(fp);
	free(guess);
	free(secret_array);
	free(word);
}
