#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define CHANCES 6
#define WORD_SIZE 36
#define GUESS_SIZE 3


int check_args(char * dictionary, char * argv[], int random);
int init_secret(size_t size, char * secret_array);
int guess_check(char * already_guessed, int * stuff, char * guess);
int converter(char * guess);
int play(size_t size, char * dictionary, char * guess, int * wrong_guesses, char * secret_array);

int main(int argc, char * argv[])
{
	srand(time(NULL));
	char * dictionary;
	int random = 0;

	dictionary = malloc(WORD_SIZE);

	//must use .hangman and .word file in the same directory as the executable hangman program otherwise seg fault

	if (argc == 1)
	{
		argv[1] = ".word"; //if no argument , default to word file
		if (1 == check_args(dictionary, argv, random))
		{
			exit(1); //if there was an error exit
		}
	}
	else if (argc == 2)
	{
		if (1 == check_args(dictionary, argv, random))
		{
			exit(1);
		}
	}			

	char * word = dictionary;
	char *guess = malloc(GUESS_SIZE);
	size_t size = strlen(word);
	char * secret_array = malloc(size);
	char * already_guessed = malloc(WORD_SIZE);
	int wrong_guesses = 0;
	FILE *stats;
	int win = 0;
	int loss = 0;
	int nofgames = 0;
	double score = 0.0;
	int stuff = 0;
	double wrong = 0;
	char plural1 = 's';
	char plural2[3] = {'e', 's', '\0'};

	word = malloc(size);

	memset(already_guessed, '\0', WORD_SIZE); //used to copy over whatever was in memory to null bytes

	if(1 != init_secret(size, secret_array)) //if a 1 does not come back then there must be an error
	{
		fprintf(stderr, "Fatal error, reopen file\n");
		exit(1);
	}

	while(1)
	{
		printf("Size of word is : %zd\n\n", (size - 1));
		printf("%s\n", secret_array);
		start:
		{
			printf("What is your guess: ");
			fgets(guess, GUESS_SIZE, stdin);


			if(0 == converter(guess))//converts and checks for if its a letter
			{
				printf("Please enter valid input\n");
				while(!strrchr(guess, '\n')){ //eats rest of stdin and asks for input again
					fgets(guess, GUESS_SIZE, stdin);
				}
				goto start;
			}

			//if a 1 does not come back then there must be an error
			if (1 != guess_check(already_guessed, &stuff, guess)) 
			{	
				fprintf(stderr, "An error occured.\n");
				exit(1);
			}

			already_guessed[stuff] = guess[0]; //fills the array with whatever if guess for later use
			already_guessed[WORD_SIZE - 1] = '\0'; //makes sure last byte is null byte
		}

		if (guess[1] == '\n')
		{
			//opens a file with read permission and ability to create is not found
			stats = fopen(".hangman", "r+");
 			//scans in previous variables
			fscanf(stats, "%d %d %d %lf %lf", &win, &loss, &nofgames, &wrong, &score);
			//closes what i opened
			fclose(stats);

 			//if 1 is returned the game is won
			if (1 == play(size, dictionary, guess, &wrong_guesses, secret_array))
			{
				printf("You win!\n");
				printf("Your word was : %s\n", secret_array);
				win++;
				break;
			}
			else if (wrong_guesses == CHANCES) //if not waits to see if wrong_guesses is 6
			{
				printf("You lose\n");
				printf("Your word was : %s\n", dictionary);
				loss++;
				break;
			}

		}
		else
		{
			printf("Not right\n");
			while(!strrchr(guess, '\n')){
				fgets(guess, GUESS_SIZE, stdin); //eats stdin and asks for input again
			}	
		}


	}
	nofgames++;
	wrong = (wrong_guesses + wrong);
	if (win > 0)
	{
		score = wrong / win;
	}
	else
	{
		score = 0;
	}


	//checks for printing win/wins loss/losses
	if (win > 1 && loss > 1)
	{
		//plural 1 and plural 2 stay 
	}
	else if (win <= 1 && loss <= 1)
	{
		plural1 = '\0';
		plural2[0] = '\0';
	}
	else if (win == 0 && loss >= 1)
	{
		plural1 = '\0';
	}

	else if (win == 1 && loss > 1)
	{
		plural1 = '\0';
	}
	else if (win > 1 && loss <= 1)
	{
		plural2[0] = '\0';
	}

	printf("Win%c: %d Loss%s: %d Number of Games: %d Total Wrong: %.2f Score: %.2f\n", plural1, win, plural2, loss, nofgames, wrong, score);
	
	//writes to file .hangman the new values to be stored
	stats = fopen(".hangman", "w+");
	fprintf(stats, "%d %d %d %.2f %.2f", win, loss, nofgames, wrong, score);

	//frees whatever I have opened
	fclose(stats);
	free(guess);
	free(secret_array);
	free(word);
	free(dictionary);
	free(already_guessed);
}


int check_args(char * dictionary, char * argv[], int random)
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
		/*
			Found this code to read from a file at
			* http://stackoverflow.com/questions/27606829/comparing-input-scanw-fgets-and-a-chosen-word-from-the-textfile-doesnt-work
		*/
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

int init_secret(size_t size, char * secret_array)
{
	for (int unsigned counter = 0; counter < size; counter++)
	{
		secret_array[counter] = '_'; //fills secret array with '_'s
	}
	secret_array[size - 1] = '\0'; //makes sure last byte is null byte
	return 1;
}

int guess_check(char * already_guessed, int * stuff, char * guess)
{

	for (int unsigned count = 0; count < WORD_SIZE; count++)
	{
		if (already_guessed[count] == guess[0]) //if guess is in already_guessed tell user
		{
			printf("You already guessed that nimrod\n");
			break;
		}
	}

	(*stuff)++; //increments stuff in main
	return 1;

}

int converter(char * guess)
{
	if (*guess >= 'a' && *guess <= 'z') //changes to uppercase if between a and z , also works as type checker
	{
		*guess = ('A' + *guess - 'a');
		return 1;
	}
	else
	{
		return 0;
	}
}

int play(size_t size, char * dictionary, char * guess, int * wrong_guesses, char * secret_array)
{
	int unsigned count;
	int winner;
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
			"       ====\n"
	};

	int tracker = 1;

	for (count = 0; count < size; ++count)
	{
		if (dictionary[count] == guess[0])
		{
			secret_array[count] = guess[0];
			tracker = 0;
		}
	}

	if (tracker == 1)
	{
		(*wrong_guesses)++;
		printf("%s\n", hung[*wrong_guesses]);
	}


	printf("Wrong guesses are : %d\n\n", *wrong_guesses);
	tracker = 1;

	for (count = 0; count < size; ++count)
	{
		if (secret_array[count] == '_')
		{
			winner = 0;
			break;	
		}
		else
		{
			winner = 1;
		}
	}

	return winner;
}
