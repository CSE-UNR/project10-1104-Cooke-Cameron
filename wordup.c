#include <stdio.h>

#define WORDLENGTH 5
#define MAXGUESSES 6

int getWord(char target[]);
void promptWord (char guess[], int guessNumber);
void separator();
void checkGuess(char guess[], char target[], int correct[], int misplaced[]);
void displayGuess( char guess[][WORDLENGTH + 1], int corrects[][WORDLENGTH], int misplaceds[][WORDLENGTH], int round);
void results(int win, char target[]);
int correctGuess(char guess[], char target[]);


int main() {

	char target[WORDLENGTH + 1];
	if (!getWord(target)) {
		return 1;
	}
	
	for (int i = 0; i < WORDLENGTH; i++) {
		if (target[i] >= 'A' && target[i] <= 'Z') {
			target[i] += 'a' - 'A';
		}
	}
	
	char guesses[MAXGUESSES][WORDLENGTH + 1];
	int correct[MAXGUESSES][WORDLENGTH];
	int misplaced[MAXGUESSES][WORDLENGTH];
	int round = 0;
	int win = 0;

	while (round < MAXGUESSES) {
		promptWord(guesses[round], round + 1);
		separator();
		checkGuess(guesses[round], target, correct[round], misplaced[round]);
		displayGuess(guesses, correct, misplaced, round + 1);
		
		if (correctGuess(guesses[round], target)) {
			win = 1;
			break;
		}
		round++;
	}
	
	results(win, target);
	
	
	
	return 0;
}

void promptWord(char userWord[WORDLENGTH + 1], int guessNumber) {
	
	printf("Guess %d! Enter your guess: ", guessNumber);
	
	while (1) {
	
	int invalid = 0;
	int length = 0;
	
	scanf("%s", userWord);
	
	while (userWord[length] != '\0') {
		char check = userWord[length];
			if (!((check >= 'A' && check <= 'Z') || (check >= 'a' && check <= 'z'))) { 
			invalid = 1;
	}
			else if (check >= 'A' && check <= 'Z') {
			userWord[length] = check + ('a' - 'A');
			}
		length++;
	}
	
	if (length != 5 && invalid == 1) {
		printf("Your guess must be 5 letters long. Your guess must contain only letters.\n");
		printf("Please try again: ");
	}
	else if (length != 5) {
		printf("Your guess must be 5 letters long.\n");
		printf("Please try again: ");
	}
	else if (invalid == 1) {
		printf("Your guess must contain only letters.\n");
		printf("Please try again: ");
	}
	else {
		break;
	}
	}
}

int getWord(char target[]) {
	
	FILE*file = fopen("word.txt", "r");
		if (file == NULL) {
			printf("File unsuccessfully opened\n");
			return 0;
		}
	fscanf(file, "%s", target);
	fclose(file);
	
	return 1;
	
}

void separator() {
	printf("================================\n");
}

void checkGuess(char guess[], char target[], int correct[], int misplaced[]) {
	
	int used[WORDLENGTH] = {0};
	
	for (int i = 0; i < WORDLENGTH; i++) {
		correct[i] = (guess[i] == target[i]);
		misplaced[i] = 0;
			if (correct[i]) {
				used[i] = 1;
			}
	}	

	for (int i = 0; i < WORDLENGTH; i++) {
		if (!correct[i]) {
			for (int j = 0; j < WORDLENGTH; j++) {
				if (!used[j] && guess[i] == target[j]) {
					misplaced[i] = 1;
					used[j] = 1;
					break;
				}
			}
		}
}

}
void displayGuess(char guesses[][WORDLENGTH + 1], int corrects[][WORDLENGTH], int misplaceds[][WORDLENGTH], int round) {
	for (int r = 0; r < round; r++) {
		// Print the word
		for (int i = 0; i < WORDLENGTH; i++) {
			char c = guesses[r][i];
			if (corrects[r][i] && c >= 'a' && c <= 'z') {
				c -= 'a' - 'A';
			}
			printf("%c", c);
		}
		printf("\n");
		// Print the misplaced markers
		for (int i = 0; i < WORDLENGTH; i++) {
			printf("%c", misplaceds[r][i] ? '^' : ' ');
		}
		printf("\n");
	}
}

int correctGuess(char guess[], char target[]) {
	for ( int i = 0; i < WORDLENGTH; i++) {
		if (guess[i] != target[i]) {
			return 0;
		}
	}
	return 1;
}

void results(int win, char target[]) {
	if(win) {
		printf("Congratulations, You Won!", target[);
		printf("GOATED");
	}
	else {
		printf("Out of Guesses!\n");
	}
}





