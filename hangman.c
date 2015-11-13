#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define CHANCES 6
#define WORD_SIZE 36
#define GUESS_SIZE 3


int checker(char * dictionary, char * argv[], int random);
int init_secret(int unsigned counter, size_t size, char * secret_array);

int main(int argc, char * argv[])
{
	srand(time(NULL));
	char * dictionary;
	char *guess;
	int random = 0;

	guess = malloc(GUESS_SIZE);
	dictionary = malloc(WORD_SIZE);

	if (argc == 1)
	{
		argv[1] = "words.txt";
		if (1 == checker(dictionary, argv, random))
		{
			exit(1);
		}
	}
	else if (argc == 2)
	{
		if (1 == checker(dictionary, argv, random))
		{
			exit(1);
		}
	}

	/* Learned the ability to print out my hang man from
		* stackoverflow.com/revisions/22965820/1
	*/

	char * hung[] = {
			"  =======|\n"
			"         |\n"
			"         |\n"
			"         |\n"
			"       ====\n",
			"  |======|\n"
			"  o      |\n"
			"         |\n"
			"         |\n"
			"       ====\n",
			"  |======|\n"
			"  o      |\n"
			"  |      |\n"
			"         |\n"
			"       ====\n",
			"  |======|\n"
			"  o      |\n"
			" /|      |\n"
			"         |\n"
			"       ====\n",
			"  |======|\n"
			"  o      |\n"
			" /|\\     |\n"
			"         |\n"
			"       ====\n",
			"  |======|\n"
			"  o      |\n"
			" /|\\     |\n"
			" /       |\n"
			"       ====\n",
			"  |======|\n"
			"  o      |\n"
			" /|\\     |\n"
			" / \\     |\n"
			"       ====\n",
	};


			
	char * word = dictionary;
	int unsigned count = 0;
	int wrong_guesses = 0;
	int tracker = 1;
	int winner = 1;
	int already = 1;
	size_t size = strlen(word);
	char * secret_array = malloc(size);
	FILE *stats;
	int win = 0;
	int loss = 0;
	int nofgames = 0;
	float score = 0.0;

	word = malloc(size);


	if(1 != init_secret(count, size, secret_array))
	{
		printf("Fatal error, reopen file\n");
		exit(1);
	}


	while(1)
	{
		printf("Size of word is : %zd\n\n", (size - 1));
		printf("%s\n", secret_array);
		
		printf("What is your guess: ");
		fgets(guess, 6, stdin);

		if (*guess >= 'a' && *guess <= 'z')
		{
			*guess = ('A' + *guess - 'a');
		}


		for (count = 0; count < size; ++count)
		{
			if (secret_array[count] == guess[0])
			{
				printf("Already in guess\n\n");
				already = 0;
			}
		}

		if (guess[1] == '\n')
		{
			for (count = 0; count < size; ++count)
			{
				if (already == 1)
				{
					if (dictionary[count] == guess[0])
					{
						secret_array[count] = guess[0];
						//correct_guesses++ counter
						tracker = 0;
					}
				}
				else
				{
					if (dictionary[count] == guess[0])
					{
						tracker = 0;
					}
				}
			}

			if (tracker == 1)
			{
				printf("That was not in the word\n\n");
				wrong_guesses++;
				printf("%s\n", hung[wrong_guesses]);
				//wrong_guesses++;
			}


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
			fscanf(stats, "%d %d %d %f", &win, &loss, &nofgames, &score);

			fclose(stats);

			if (winner == 1)
			{
				printf("You win\n");
				win++;
				break;
			}
			else if (wrong_guesses == (CHANCES + 1))
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
	nofgames++;
	score = wrong_guesses / win;
	
	printf("Win: %d\tLoss: %d\t Number of Games: %d\t Score: %.2f\n", win, loss, nofgames, score);

	stats = fopen("hangman.txt", "w+");
	fprintf(stats, "%d %d %d %.2f", win, loss, nofgames, score);

	fclose(stats);
	free(guess);
	free(secret_array);
	free(word);
	free(dictionary);
}


int checker(char * dictionary, char * argv[], int random)
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
		for (; fgets(dictionary, WORD_SIZE, fp); random++)
		{
			;
		}
		ran = (rand() % random);
		rewind(fp);

		for (int c = 0; c < ran; c++)
		{
			fgets(dictionary, WORD_SIZE, fp);
		}

	}
	fclose(fp);
	return 0;
}

int init_secret(int unsigned counter, size_t size, char * secret_array)
{
	for (counter = 0; counter < size; counter++)
	{
		secret_array[counter] = '_';
	}
	secret_array[size - 1] = '\0';
	return 1;
}
