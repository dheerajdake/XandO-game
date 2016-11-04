/* Author: Dheeraj Dake
 * Date:   10/31/16
 * Description: The classic X and O game
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

#define ROWS 3
#define COLUMNS 3

char **createMatrix(int rows, int columns);
void playGame(int option, char pick, char **board);
void printBoard(char **board);
bool isStrike(char **board);

int main()
{
	setbuf(stdout, NULL);

	printf("The classic X and O game is back\n");
	printf("Game rules: \n");
	printf("--> Player chooses either X or O. The player who gets the first strike with his character wins\n");

	//Show empty board
	int a;
	for(a=0; a<3; a++)
		printf("__|__|__\n");

	//Player options
	int option;
	char pick;

	printf("Choose an option: \n");
	printf("Enter 1 to play with computer and 2 for two players: ");
	scanf("%d", &option);

	printf("Choose X or O: ");
	getchar();					//For the newline character
	scanf("%c", &pick);

	srand(time(NULL));
	char **gameBoard = createMatrix(ROWS, COLUMNS);
	playGame(option, pick, gameBoard);

	//Free memory
	int f;
	for(f=0; f<ROWS; f++)
		free(gameBoard[f]);
	free(gameBoard);
	gameBoard = NULL;
	return 0;
}

char **createMatrix(int rows, int columns)
{
	char **board = (char **)malloc(rows*sizeof(char *));
	int a;
	for(a=0; a<columns; a++)
	{
		board[a] = (char*)malloc(columns*sizeof(char));
	}

	//Fill the board with spaces
	int r,c;
	for(r=0; r<rows; r++)
	{
		for(c=0; c<columns; c++)
		{
			board[r][c] = ' ';
		}
	}
	return board;
}

void playGame(int option, char pick, char **board)
{
	char second_pick;
	if(pick == 'X')
	{
		second_pick = 'O';
	}
	else if(pick == 'O')
	{
		second_pick = 'X';
	}

	if(option == 1) //play with computer
	{
		/*printf("Computer chose %c\n", second_pick);
		int r = rand()%3;
		int c = rand()%3;
		if(r%2 == 0)
		{
			printf("Player starts\n");
		}
		else
		{
			printf("Computer starts\n");
			board[r][c] = second_pick;
		}*/

		//Use MinMax algo here and build AI
		printf("Check back afterwards. Thank you \n");
		return;
	}
	else if(option == 2) //play with another player
	{
		printf("Player 2's pick: %c\n", second_pick);
	}

	printBoard(board);
	int r=0, c=0, player=0;;
	switch(option)
	{
		case 1:			//computer
			while(1)
			{
				if(!isStrike(board))
				{
					printf("Enter row and column for your pick to be placed: \n");
					scanf("%d %d", &r, &c);
					getchar();
					board[r][c] = pick;
					printBoard(board);
				}


				//computer turn
				//simulation needs to be taught
			}
			break;
		case 2:
			while(1)
			{
				if(!isStrike(board))
				{
					printf("Player 1 turn: \n");
					scanf("%d %d", &r, &c);
					board[r][c] = pick;
					printBoard(board);

					if(isStrike(board))
					{
						player = 1;
						break;
					}

					printf("Player 2 turn: \n");
					scanf("%d %d", &r, &c);
					board[r][c] = second_pick;
					printBoard(board);
				}
				else
				{
					break;
				}
			}
			if(player == 1)
				printf("Hurray! Player 1 wins!!!");
			else
				printf("Hurray! Player 2 wins!!!");
			break;
		default:
			break;
	}
}

void printBoard(char **board)
{
	int r,c;
	printf(" - - - \n");
	for(r=0; r<ROWS; r++)
	{
		for(c=0; c<COLUMNS; c++)
		{
			printf("|%c", board[r][c]);
		}
		printf("|\n");
		printf(" - - - \n");
	}
}

bool isStrike(char **board)
{
	//Monitor rows, columns and diagonals for strike
	int r,c;
	for(r=0; r<ROWS; r++)
	{
		if(((board[r][0] == 'X') && (board[r][1] == 'X') && (board[r][2] == 'X')) || ((board[r][0] == 'O') && (board[r][1] == 'O') && (board[r][2] == 'O')))
			return true;
	}

	for(c=0; c<COLUMNS; c++)
	{
		if(((board[0][c] == 'X') && (board[1][c] == 'X') && (board[2][c] == 'X')) || ((board[0][c] == 'O') && (board[1][c] == 'O') && (board[2][c] == 'O')))
			return true;
	}

	if(((board[0][0] == 'X') && (board[1][1] == 'X') && (board[2][2] == 'X')) || ((board[0][0] == 'O') && (board[1][1] == 'O') && (board[2][2] == 'O')))
		return true;
	else if(((board[0][2] == 'X') && (board[1][1] == 'X') && (board[2][0] == 'X')) || ((board[0][2] == 'O') && (board[1][1] == 'O') && (board[2][0] == 'O')))
		return true;
	else
		return false;
}
