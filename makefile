
CFLAGS+=-g -std=c11 -Wall -Wextra -pedantic -Wno-deprecated -Wstack-usage=1024

hangman: hangman.c
	gcc -g -std=c11 -Wall -Wextra -pedantic -Wno-deprecated -Wstack-usage=1024 -o hangman hangman.c -lm

debug: CFLAGS+=-g
debug: hangman

clean:
	-rm hangman

