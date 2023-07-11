#include "hangman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int get_word(char secret[]) {
  // check if file exists first and is readable
  FILE *fp = fopen(WORDLIST_FILENAME, "rb");
  if (fp == NULL) {
    fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
    return 1;
  }

  // get the filesize first
  struct stat st;
  stat(WORDLIST_FILENAME, &st);
  long int size = st.st_size;

  do {
    // generate random number between 0 and filesize
    long int random = (rand() % size) + 1;
    // seek to the random position of file
    fseek(fp, random, SEEK_SET);
    // get next word in row ;)
    int result = fscanf(fp, "%*s %20s", secret);
    if (result != EOF)
      break;
  } while (1);

  fclose(fp);

  return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]) {
  int guessed = 0;
  for (int i = 0; i < strlen(secret); i++) {
    for (int j = 0; j < strlen(letters_guessed); j++) {
      if (secret[i] == letters_guessed[j]) {
        guessed++;
      }
    }
  }
  return guessed == strlen(secret);
}

void get_guessed_word(const char secret[], const char letters_guessed[],
                      char guessed_word[]) {
  for (int i = 0; i < strlen(secret); i++) {
    guessed_word[i] = '_';
    for (int j = 0; j < strlen(letters_guessed); j++) {
      if (secret[i] == letters_guessed[j]) {
        guessed_word[i] = secret[i];
      }
    }
  }
  printf("%s\n", guessed_word);
}

void get_available_letters(const char letters_guessed[],
                           char available_letters[]) {
  for (int i = 0; i < 26; i++) {
    int guessed = 0;

    for (int j = 0; j < strlen(letters_guessed); j++) {
      if (letters_guessed[j] == 'a' + i) {
        guessed = 1;
      }
    }

    if (guessed == 0) {
      printf("%c", 'a' + i);
    }
  }
  printf("\n");
}

void hangman(const char secret[]) {
  int try = 0;
  int guesses = 8;
  int neviem = 0;
  int uhadnute = 0;
  char letters_guessed[26];
  char available_letters[26];
  char guessed_word[strlen(secret)];

  printf("Welcome to the game, Hangman!\n");
  printf("I am thinking of a word that is %ld letters long.\n", strlen(secret));

  do {
    printf("-------------\n");
    printf("You have %d guesses left.", guesses);
    printf("Available letters: ");
    get_available_letters(letters_guessed, available_letters);
    printf("Please guess a letter: ");
    scanf(" %c", &letters_guessed[try]);

    if (letters_guessed[try] < 'A' || letters_guessed[try] > 'z') {
      printf("Oops! '%c' is not a valid letter: ", letters_guessed[try]);
    } else if (letters_guessed[try] > 'Z' && letters_guessed[try] < 'a') {
      printf("Oops! '%c' is not a valid letter: ", letters_guessed[try]);
    } else {
      if (letters_guessed[try] >= 'A' && letters_guessed[try] <= 'Z') {
        letters_guessed[try] += ' ';
      }

      uhadnute = 0;
      for (int i = 0; i < strlen(secret); i++) {
        if (letters_guessed[try] == secret[i]) {
          uhadnute++;
        }
      }
      if (uhadnute == neviem) {
        printf("\nNeuhadol si.\n");
        uhadnute = neviem;
        guesses--;
      } else {
        printf("\nUhadol si.\n");
        uhadnute = neviem;
      }
    }
    get_guessed_word(secret, letters_guessed, guessed_word);
    try++;
  } while (is_word_guessed(secret, letters_guessed) == 0 && guesses > 0);

  if (guesses <= 0) {
    printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
  } else if (is_word_guessed(secret, letters_guessed) == 1) {
    printf("Congratulations, you won!\n");
  } else {
    printf("nieco sa dojebalo\n");
  }
}

int main() {
  char secret[30];

  get_word(secret);
  hangman("neviem");
  return 0;
}
