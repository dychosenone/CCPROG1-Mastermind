/*

	Name: Jacob Miguel C. Dy
	ID #: 11927704
	Section: S11B
	CCPROG1 Machine Project
	
	Project Name: Mastermind
	
*/	

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Declaration of Functions
int menu();
int playAgain();
int checkDigit();
int checkPosition();
void game();
int settings();
int changeGuess();


// This Function Checks for the # of Correct Digits found after checking for the # of Correct Positions
int checkDigit(int guess, int random){
	
	int guessCounter = guess;
	int guessDigit;
	int multiplier = 1;

	int randomDump = 0;
	int guessChecker;
	int randomChecker;
	
	int digitCountFinal;
	
	// This gets the # of digits
	for(guessDigit = 0; guessCounter > 0; guessDigit++){
		guessCounter /= 10;
	}
	
	digitCountFinal = 0;
	
	//Checks all values of Guess and Random to see which digit is equal
	for(; guessDigit > 0; guessDigit--){
		
		guessChecker = guess % 10;
		
		while(random > 0){
			
			randomChecker = random % 10;
			
			// If the value is equal, increment digitCountFinal. But if not place value into a dump to check again later for other values of guess.
			if(randomChecker == guessChecker){
				digitCountFinal++;
			}
			else{
				randomDump = randomDump + (randomChecker * multiplier);
				multiplier *= 10;
			}
			
			random /= 10;
		}
		
		random = randomDump;
		randomDump = 0;
		multiplier = 1;
		
		guess /= 10;
			
	}
	
	return digitCountFinal;
}

//This function checks for the number of correct positions
int checkPosition(int first, int random, int *correctDigit){
	int value1;
	
	int value2;
	
	int correctDigitRandom = 0;
	int correctDigitGuess = 0;
	
	int multiplier = 1;
	
	int correctPosition = 0;
	
	//Loops to see which position values are equal to each other.
	while(first > 0, random > 0){
		value1 = first % 10;
		value2 = random % 10;
		
		first = (first - value1) / 10;
		random = (random - value2) / 10;
		
		if(value1 == value2){
			correctPosition++;
		}	
		//Adds all the remaining guess and random values that don't have correct position into a variable.		
		else if(value1 != value2){
			correctDigitRandom += (value2 * multiplier);
			correctDigitGuess += (value1 * multiplier);
			
			multiplier *= 10;
		}
	}
	
	//Calls checkDigit() to see which values have correct digit
	*correctDigit = checkDigit(correctDigitRandom, correctDigitGuess);
	
	
	return correctPosition;
}

//This function generates a random 4 Digit Number
int randomNumber(){
	
	int i, randomNumber = 0;
	
	srand(time(0));
	//Generates one digit and then multiplies. This creates a 4 digit random number.
	for(i = 1; i < 10000; i *= 10){
		
		randomNumber = randomNumber + (((rand() % 9) + 1)) * i;
		
	}
	
	return randomNumber;
	
}		

/*This function verifies if the input value follows the following:
	1. No Zeroes in any of the digits.
	2. Max value for digits is 9
	3. Min value for digits is 1
	4. There are 4 digits
*/
int verifyValue(int input){

	int checkZero = input;
	int checkDigits = input;
	int checkValue;
	int digits = 0;
	
	//Checks whether digits have zeroes.	
	while(checkZero > 0){
		
		checkValue = checkZero % 10;
		
		if(checkValue > 0 && checkValue <= 9){
			checkZero /= 10;
		}
		else{
			return 1;
			checkZero = 0;
		}
	}
	
	//Counts number of digits to be used in the conditional statement below.
	while(checkDigits > 0){
		digits++;
		checkDigits /= 10;
	}
	
	//If Input is not 1 (1 is used to view random sequence) then checks if digits are only 4 digits.
	if(input != 1){	
	
		if(digits > 4 || digits < 4){
			return 1;
		}
		else {
			return 0;
		}
	}
	else if(input == 1) {
		return 0;
	}
	
}

/* This function initializes a new game.*/

void game(int players, int guess){
	int menuOption;
	
	//Creates a random sequence of numbers.
	int random = randomNumber();
	
	int guessGame = guess;
	
	int win = 0;
	int winner;
	
	int totalPlayers = players;
	int currentPlayer = 1;
	int inputValue;
	
	int guessOne;
	int guessTwo;
	
	int positionOne;
	int positionTwo;
	
	int winCheck;
	int winCheckDigit;
	
	int correctDigitOne;
	int correctDigitTwo;
	
	//If value of guess = 1, this will be set to true. While this is true, random value will be shown every time a player makes a guess.
	int showRandom = 0;
	
	//If this is true, then it will loop until the guess value is correct (Correct is 0).
	int verifyGuess = 0;
	
	printf("\n\t********************************************************* \n");
	printf("\t*                                                       * \n");
	printf("\t*\t              Instructions\t\t\t*\n");
	printf("\t*\t    A is the number of exact matches \t\t*\n");
	printf("\t*\t    B is the number of correct digits\t\t*\n");
	printf("\t*\t    Press [1] to show Secret Sequence \t\t*\n");
	printf("\t*                                                       * \n");
	printf("\t********************************************************* \n\n");
	
	
	//Function that loops and only ends when the guess is 0 or when win is 1.
	do{
		
		for(; totalPlayers >= currentPlayer && win == 0; currentPlayer++){	
			
			if(showRandom == 1){
				printf("Random Value: %d\n", random);
			}
			
			printf("Player %d Input Guess: ", currentPlayer);
			scanf("%d", &inputValue);
			
			verifyGuess = verifyValue(inputValue);
			
			while(verifyGuess == 1){
				
				printf("Error: Invalid Input. \n");
				printf("\nNumber of Guesses Left: %d\n", guess);
				printf("Player %d Input Guess: ", currentPlayer);
				scanf("%d", &inputValue);
			
				verifyGuess = verifyValue(inputValue);	
			}
			
			
			if(inputValue == 1){
				showRandom = 1;
				
				printf("\nRandom Value: %d\n", random);
				
				printf("Player %d Input Guess: ", currentPlayer);
				scanf("%d", &inputValue);
				
				verifyGuess = verifyValue(inputValue);	
				
				while(verifyGuess == 1){
				
					printf("Error: Invalid Input. \n");
					printf("\nNumber of Guesses Left: %d\n", guess);
					printf("Player %d Input Guess: ", currentPlayer);
					scanf("%d", &inputValue);
			
					verifyGuess = verifyValue(inputValue);	
				}
				
			}		
			
			winCheck = checkPosition(inputValue, random, &winCheckDigit);
			
			//When position is 4, it sets the win variable to true, then sets the winner to the current player.
			if(winCheck == 4){
				win = 1;
				winner = currentPlayer;
			}
			
			if(currentPlayer == 1){
				guessOne = inputValue;
			}
			if(currentPlayer == 2){
				guessTwo = inputValue;
			}
			
		}
		currentPlayer = 1;
		guess--;
		
		//Checks the position of both guesses.
		positionOne = checkPosition(guessOne, random, &correctDigitOne);
		positionTwo = checkPosition(guessTwo, random, &correctDigitTwo);
		
		
		
		printf("\n\t********************************************************* \n");
		printf("\t*                                                       * ");
		printf("\n\t*\t     Number of Guesses Left: %d\t\t\t*\n", guess);
		printf("\t*                                                       * \n");
		printf("\t*\tPlayer 1: \t\t Player 2: \t\t*\n");
		printf("\t*\tGuess: %d \t\t Guess: %d \t\t*\n", guessOne, guessTwo);
		printf("\t*\tScore: %dA %dB \t\t Score: %dA %dB \t\t*\n",positionOne,correctDigitOne,positionTwo,correctDigitTwo);
		printf("\t*                                                       * \n");
		printf("\t********************************************************* \n\n");
					
				
	}while(win == 0 && guess != 0);
	
	//If guess is 0, shows that the game is a draw.
	if(guess == 0){
		
		printf("\t\t*****************************************\n");
		printf("\t\t*                                       *");
		
		printf("\n\t\t*   There is no winner for this round.\t*\n");
		printf("\t\t*\t   The game is a tie. \t\t*\n");
		printf("\t\t*\t   Random Value: %d \t\t*\n", random);
		
		printf("\t\t*                                       *\n");
		printf("\t\t*****************************************\n");
		
		playAgain(players, guessGame);
	}
	
	//If win is true, then it prints out the winner, random value and guess.
	if(win == 1){
		// If there is a winner!
		
		printf("\t\t*****************************************\n");
		printf("\t\t*                                       *");
		printf("\n\t\t*\tCongratulations!!! \t\t*\n");
		printf("\t\t*\tPlayer %d wins this round!\t*\n", winner);
		
		printf("\t\t*\tRandom Value: %d\t\t*\n", random);
		printf("\t\t*\t# of Guesses made: %d \t\t*\n", guessGame - guess);
		printf("\t\t*                                       *\n");
		printf("\t\t*****************************************\n");
		
		playAgain(players, guessGame);
		
	}
	
}	

// This function changes the Max number of guesses.
int changeGuess(){
	
	int newGuessValue;
	
	printf("Input Guess Value: ");
	scanf("%d", &newGuessValue);

	while(newGuessValue > 20 || newGuessValue < 1){
		printf("Error: Value Should be between 1 and 20. \n");
		printf("Input Guess Value: ");
		scanf("%d", &newGuessValue);
	}
			
	return newGuessValue;
}

// This function initializes the settings page.

int settings(int players, int guess){
	int settingsOption;
	int gameInfoExit;
	
	printf("\t--------------------------------------------- \n");
	printf("\t\t\t|| Settings ||\n");
	printf("\t--------------------------------------------- \n");
	
	printf("Current # of Players: %d\n", players);
	printf("Current Maximum Guess: %d\n\n", guess);
	
	
	do{
		printf("Select an option:\n");
	
		printf("\t[1] Game Info\n");
		printf("\t[2] Change Guess Value\n");
		printf("\t[3] Back\n");
		scanf("%d", &settingsOption);
	}while(settingsOption != 1 && settingsOption != 2 && settingsOption != 3);
	
	switch(settingsOption){
		case 1: 
			printf("\t********************************************************* \n");
			printf("\t*                                                       * \n");
			printf("\t*\t     Mastermind Software by: Jacob Dy\t\t*\n");
			printf("\t*\t  This is a two-player code breaking game \t*\n");
			printf("\t*\t     based on the classic board game\t\t*\n");
			printf("\t*\t\t    of the same name \t\t\t*\n");
			printf("\t*                                                       * \n");
			printf("\t********************************************************* \n");
			
			printf("Press [1] to exit to settings. \n");
			scanf("%d", &gameInfoExit);
			
			if(gameInfoExit == 1){
				settings(players, guess);	
				gameInfoExit = 0;
			}
			break;
		case 2:
			guess = changeGuess();
			settings(players, guess);
			break;
		case 3:
			menu(players, guess);
			break;
		default:  
			/* printf("Not a valid option. Try again.\n"); */
			
			printf("Select an option:\n");
	
			printf("\t[1] New Game\n");
			printf("\t[2] Settings\n");
			printf("\t[3] Exit\n");
			
			scanf("%d", &settingsOption);
			break;
	
		}
	
	
}

// This function initializes the menu page.

int menu(int players, int guess){
	int menuOption;
	
	printf("\t--------------------------------------------- \n");
	printf("\t\t|| Welcome to Mastermind! ||\n");
	printf("\t--------------------------------------------- \n\n");
	
	printf("\t--------------------------------------------- \n");
	printf("\t|\tSelect an option:\t\t    |\n");
	
	printf("\t|  \t[1] New Game\t\t\t    |\n");
	printf("\t|  \t[2] Settings\t\t\t    |\n");
	printf("\t|  \t[3] Exit\t\t\t    |\n");
	printf("\t--------------------------------------------- \n");
	printf("Input: ");
	scanf("%d", &menuOption);

	//While input is not correct, loop the menu screen.
	while(menuOption != 1 && menuOption != 2 && menuOption != 3){
		printf("Error: Invalid Input. \n");
		printf("\t--------------------------------------------- \n");
		printf("\t|\tSelect an option:\t\t    |\n");
		
		printf("\t|  \t[1] New Game\t\t\t    |\n");
		printf("\t|  \t[2] Settings\t\t\t    |\n");
		printf("\t|  \t[3] Exit\t\t\t    |\n");
		printf("\t--------------------------------------------- \n");
		printf("Input: ");
		scanf("%d", &menuOption);
	}
		
	switch(menuOption){
		case 1: 
			game(players, guess);
			break;
		case 2:
			settings(players, guess);
			break;
		case 3:
			printf("\t--------------------------------------------- \n");
			printf("\t|      Thank you for playing! Goodbye! \t    |\n");
			printf("\t--------------------------------------------- \n\n");
			break;
		default:  
			/* printf("Not a valid option. Try again.\n"); */
			
			printf("*\tSelect an option:\n");
	
			printf("*\t[1] New Game\t*\n");
			printf("*\t[2] Settings\t*\n");
			printf("*\t[3] Exit\t*\n");
			
			scanf("%d", &menuOption);
			break;
	
		}
}


// This function asks if the player wants to play another round.
int playAgain(int players, int guess){
	int menuOption;
		
		do{
			printf("\nWould You like to play again? \n");
			printf("[1] Yes / [2] No\n");
			scanf("%d", &menuOption);
		} 
		while(menuOption != 1 && menuOption != 2);
		
		switch(menuOption){
			case 1:
				game(players, guess);
				break;
			case 2:
				menu(players, guess);
				break;
		}
	
}

int main(){
	
	//Intializes the two main variables.
	int players = 2;
	int guess = 10;		
	
	//Shows the menu screen
	menu(players, guess);
		
    return 0;
}
