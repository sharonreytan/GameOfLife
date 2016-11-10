
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COLS 32
#define ROWS 32
void user_menu();//lets the user choose what to play with
void print_matrix(int[][COLS], int, int);//prints a matrix for the game, with * or blank
void input_matrix(int[][COLS], int, int);//gets from the user values for dead or alive
void input_matrix_rand(int[][COLS], int, int);//fills the matrix randomly for dead and alive
int dead_or_alive(int[][COLS], int, int);//calculates each cell's new state
int game(int [][COLS], int , int);// runs the game and print the matrixes
int equal_matrix(int[][COLS], int[][COLS], int, int);//checks if two matrixes are the same, in order to exit if the current stage is the final one


void main()
{
	user_menu();
}
void user_menu()
{
	int bye,answer, answer2, n, m, board[ROWS][COLS] = { 0 };
	printf("Please choose if you want to define the size of your board game: \n{1}-To define the size \n{2}-To play with the default board\n");
	scanf_s("%d", &answer);
	if (answer == 1)
	{
		printf("Please enter the number of ROWS and COLUNMS of your board (up to 30 each)\n");
		scanf_s("%d%d", &n, &m);
		if (n>30 || m>30 || n<1 || m<1)
		{
			printf("Sorry, invalid input. Restarting program.\n");
			printf("\n");
			user_menu();
		}
		printf("Would you like to fill the matrix manualy or randomly? \n{1}- For manualy fill\n{2}- For randomly fill\n");
		scanf_s("%d", &answer2);
		if (answer2 == 1)
		{
			input_matrix(board, n, m);
			bye=game(board, n, m);
			if(bye==0) return;
		}
		if (answer2 == 2)
		{
			input_matrix_rand(board, n, m);
			bye=game(board, n, m);
			if(bye==0) return;
		}
		if (answer2 != 1 && answer2 != 2)
		{
			printf("Sorry, invalid input. Restarting program.\n");
			printf("\n");
			user_menu();
		}
	}
	if (answer == 2)
	{
		printf("Would you like to fill the matrix manualy or randomly? \n{1}- For manualy fill\n{2}- For randomly fill\n");
		scanf_s("%d", &answer2);
		if (answer2 == 1)
		{
			input_matrix(board, ROWS - 2, COLS - 2);
			bye=game(board, ROWS-2,COLS-2);
			if(bye==0) return;
		}
		if (answer2 == 2)
		{
			input_matrix_rand(board, ROWS - 2, COLS - 2);
			bye=game(board, ROWS - 2, COLS - 2);
			if(bye==0) return;
		}
		if (answer2 != 1 && answer2 != 2)
		{
			printf("Sorry, invalid input. Restarting program.\n");
			printf("\n");
			user_menu();
		}
	}

	if (answer != 1 && answer != 2)
	{
		printf("Sorry, invalid input. Restarting program.\n");
		printf("\n");
		user_menu();
	}
}
void print_matrix(int board[][COLS], int rows, int cols)
{
	int i, j;
	for (i = 1; i<=rows; i++)
	{
		printf("|");
		for (j = 1; j <= cols; j++)
		{
			if (board[i][j] == 1)
				printf("*|");
			else printf(" |");
		}
		printf("\n");
	}
}
void input_matrix(int board[][COLS], int rows, int cols)
{
	int i, j;
	printf("Enter the values of the matrix sized %d x %d.\n 1 for alive, 0 for dead \n", rows, cols);
	for (i = 1; i <= rows; i++)
		for (j = 1; j <= cols; j++)
			scanf_s("%d", &board[i][j]);
	print_matrix(board, rows, cols);
}
void input_matrix_rand(int board[][COLS], int n, int m)
{
	int i, j;
	srand(time(NULL));
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			board[i][j] = rand() % 2;
	printf("The randomly filled matrix:\n");
	print_matrix(board, n, m);
}
int dead_or_alive(int board[][COLS], int row, int col)
{
	int k, l, neighbors;
	neighbors = 0;
	for (k = -1; k<=1;k++)
	{
		for (l = -1; l <= 1; l++)
		{
			if (k != 0 || l != 0)
			{
				neighbors = neighbors + board[row + k][col + l];
				if (neighbors == 4)
					return 0;
			}
		}	
	}
	if (board[row][col] == 1)
	{
		if (neighbors <= 1)
			return 0;
		else
			return 1;
	}
	if (board[row][col] == 0)
	{
		if (neighbors == 3)
			return 1;
		else 
			return 0;
	}
	return 0;
}

int game(int board[][COLS], int rows, int cols)
{
	int i, j, next[ROWS][COLS] = { 0 };
	for (i = 1; i <= rows; i++)
	{
		for (j = 1; j <= cols; j++)
				next[i][j] = dead_or_alive(board, i, j);
	}
	printf("\nThe next stage is: \n\n");
	print_matrix(next, rows, cols);
	i = equal_matrix(board, next, rows, cols);
	if (i == 1)
	{
		printf("This is the final state. Thank you for playing the game of life.\nWould you like to play again? \n{1}-Yes \n{0}-No\n");
		scanf("%d", &i);
		if (i == 1)
			user_menu();
		else
			return 0;
	}

	printf("Would you like to continue? \n{0}-No \n{1}-Yes\n");
	scanf_s("%d", &i);
	if (i == 0)
	{
		printf("Thank you for playing the game of life.\n");
		return 0;
	}
	else game(next, rows, cols);
	return 0;
}

int equal_matrix(int board1[][COLS], int board2[][COLS], int row, int col)
{
	int i, j;
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
			if (board1[i][j] != board2[i][j])
				return 0;
	}
	return 1;
}