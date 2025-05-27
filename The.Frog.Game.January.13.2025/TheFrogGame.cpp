#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;
/*
	The Frog Game

	In N x N game board, information about the blue frog and red frog is given, and 
	the red frog removes the blue frog by jumping the blue frog in the right, left, top, and
	bottom.

	Write a program that finds the smallest number of frogs and prints the smallest number
	of blue frog remaining as answer.

*/
#define MAX 5
#define BLUE_FROG 1
#define RED_FROG 2

int matrix[MAX][MAX];
int N = 0;
int totalBlueFrogs = 0;
int totalBlueFrogsInDFS = 0;
int minFrog = INT_MAX;
int deltaCoords[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };

bool visitedMatrix[MAX][MAX];
/*
	00 01 02 {-1,0},{0,1},{1,0},{0,-1}
	10 11 12
	20 21 22
*/

struct Frog
{
	int row;
	int col;
	int blueFrogs;

	Frog(int r, int c, int cntBlueFrogs):
		row(r),
		col(c),
		blueFrogs(cntBlueFrogs){}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < N)
		return true;
	return false;
}

void dfsFrogGame(Frog& state)
{
	if (state.blueFrogs > totalBlueFrogsInDFS)
	{
		totalBlueFrogsInDFS = state.blueFrogs;
	}

	for (int coords = 0; coords < 4; ++coords)
	{
		int newRow = state.row + deltaCoords[coords][0];
		int newCol = state.col + deltaCoords[coords][1];

		if (isSafe(newRow, newCol) && matrix[newRow][newCol] == BLUE_FROG) // if there is a 1 to try to jump
		{
			int newRow = state.row + (deltaCoords[coords][0] * 2);
			int newCol = state.col + (deltaCoords[coords][1] *2 );
			if (isSafe(newRow, newCol) && matrix[newRow][newCol] == 0 && visitedMatrix[newRow][newCol] == false) // if there is a 0 to new place
			{
				//use visited matrix.
				visitedMatrix[newRow][newCol] = true;
				Frog newState(newRow, newCol, state.blueFrogs +1);
				dfsFrogGame(newState);
				visitedMatrix[newRow][newCol] = false;
			}
		}
	}
}

void mainFrogGrame(int row, int col)
{
	Frog firstState(row, col, 0);
	dfsFrogGame(firstState);
}

int main()
{
	int T = 0;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int test_cases = 0; test_cases < T; ++test_cases)
	{
		cin >> N;
		int rowFrog = 0;
		int colFrog = 0;
		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < N; ++col)
			{
				cin >> matrix[row][col];

				if (matrix[row][col] == BLUE_FROG)
				{
					totalBlueFrogs++;
				}

				if (matrix[row][col] == RED_FROG)
				{
					rowFrog = row;
					colFrog = col;
				}
			}
		}

		mainFrogGrame(rowFrog, colFrog);
		
		//int smallestNumberOfFrog = totalBlueFrogs - minFrog;
		cout << "#" << test_cases << " " << totalBlueFrogsInDFS << '\n';
		N = 0;
		totalBlueFrogs = 0;
		minFrog = INT_MAX;
	}

	return 0;
}