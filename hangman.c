#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define CHANCES 6
#define WORD_SIZE 36
#define GUESS_SIZE 3


int checker(char * dictionary, char * argv[], int i);

int main(int argc, char * argv[])
{
	srand(time(NULL));
	char * dictionary;
	char *guess;
	int i = 0;

	guess = malloc(GUESS_SIZE);
	dictionary = malloc(WORD_SIZE);

	if (argc == 1)
	{
		argv[1] = "words.txt";
		if (1 == checker(dictionary, argv, i))
		{
			exit(1);
		}
	}
	else if (argc == 2)
	{
		if (1 == checker(dictionary, argv, i))
		{
			exit(1);
		}
	}




			
	char * word = dictionary;
	int unsigned g = 0;
	int wrong_guesses = 0;
	int tracker = 1;
	int winner = 1;
	int already = 1;
	size_t size = strlen(word); //change to size_t
	char * secret_array = malloc(size);
	FILE *stats;
	int win = 0;
	int loss = 0;
	word = malloc(size);


	printf("%s\n", dictionary);
	printf("%zd\n", (size - 1));

	for (g = 0; g < size; g++)
	{
		secret_array[g] = '_';
	}
	secret_array[size - 1] = '\0';

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


			printf("Size of word is : %zd\n\n", (size - 1));
			printf("%s\n", secret_array);

			printf("Wrong guesses are : %d\n\n", wrong_guesses);
			tracker = 1;
			already = 1;

			for (int unsigned c = 0; c < size; ++c)
			{
				if (secret_array[c] == '_')
				{
					winner = 0;
					break;	
				}
				else
					winner = 1;	
			}

			stats = fopen("hangman.txt", "r+");
			fscanf(stats, "%d %d", &win, &loss);
			//printf("Win: %d\tLoss: %d\n", win, loss);

			fclose(stats);

			if (winner == 1)
			{
				printf("You win\n");
				win++;
				break;
			}
			else if (wrong_guesses == CHANCES)
			{
				printf("You lose\n");
				loss++;
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
	
	printf("Win: %d\tLoss: %d\n", win, loss);

	stats = fopen("hangman.txt", "w+");
	fprintf(stats, "%d %d", win, loss);

	fclose(stats);
	free(guess);
	free(secret_array);
	free(word);
	free(dictionary);
}


int checker(char * dictionary, char * argv[], int i)
{
	FILE *fp;
	int ran; 
	if (!(fp = fopen(argv[1], "r+")))
	{
		fprintf(stderr, "An error occured.\n");
		return 1;
	}
	else
	{
		for (; fgets(dictionary, WORD_SIZE, fp); i++)
		{
			;
		}
		ran = (rand() % i);
		rewind(fp);

		for (int c = 0; c < ran; c++)
		{
			fgets(dictionary, WORD_SIZE, fp);
		}

	}
	fclose(fp);
	return 0;
}
