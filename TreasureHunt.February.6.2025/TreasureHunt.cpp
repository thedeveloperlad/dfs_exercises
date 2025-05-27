#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;
/*
	Treasure Hunt

	There is a mine of size NxN. The mine has treasure as illustrated in figure.
	The numbers written on treasure denote the amount of treasure.

	You're given information on a mine. Write a program that find the locations of three walls
	that the miner has to tear down in order to find the maximum amount of treasure and prints that maximum
	amount.

*/

/*
	00 01 02 {-1,0},{0,1},{1,0},{0,-1}
	10 11 12
	20 21 22
*/
#define N_MAX 8

int matrix[N_MAX][N_MAX];
int N = 0;
int maximumTresuary = 0;
int matrixAux[N_MAX][N_MAX];
int minesCounter = 0;
int deltaCoords[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
bool visitedMatrix[N_MAX][N_MAX];
int matrixCost[N_MAX][N_MAX];
int temporalValue = 0;

struct Minner
{
	int row;
	int col;
	int cnt;

	Minner(int r, int c, int cn) :
		row(r),
		col(c),
		cnt(cn) {}
};

struct MinesLocation
{
	int row;
	int col;
};

MinesLocation minesLocation[N_MAX* N_MAX];

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < N)
		return true;
	return false;
}

void treasureHuntDFS(Minner& state)
{
	if (state.cnt > maximumTresuary)
	{
		maximumTresuary = state.cnt;
		return;
	}
	else
	{
		for (int delta = 0; delta < 4; ++delta)
		{
			int newRow = state.row + deltaCoords[delta][0];
			int newCol = state.col + deltaCoords[delta][1];

			if (isSafe(newRow, newCol) && (matrix[newRow][newCol] != 1) && (visitedMatrix[newRow][newCol] == false))
			{
				visitedMatrix[newRow][newCol] = true;
				state.cnt += matrix[newRow][newCol];
				Minner newState(newRow, newCol, state.cnt);
				treasureHuntDFS(newState);
				visitedMatrix[newRow][newCol] = false;
			}
		}
	}
}

void breakMines(Minner& firstState)
{
	for (int x = 0; x < minesCounter; ++x)
	{
		for (int y = x + 1; y < minesCounter; ++y)
		{
			for (int z = y; z < minesCounter; ++z)
			{
				int saveRow1 = minesLocation[x].row;
				int saveCol1 = minesLocation[x].col;

				int saveRow2 = minesLocation[y].row;
				int saveCol2 = minesLocation[y].col;

				int saveRow3 = minesLocation[z].row;
				int saveCol3 = minesLocation[z].col;
				
				matrix[minesLocation[x].row][minesLocation[x].col] = 0;
				matrix[minesLocation[y].row][minesLocation[y].col] = 0;
				matrix[minesLocation[z].row][minesLocation[z].col] = 0;

				treasureHuntDFS(firstState);
				temporalValue = 0;

				matrix[saveRow1][saveCol1] = 1;
				matrix[saveRow2][saveCol2] = 1;
				matrix[saveRow3][saveCol3] = 1;
			}
		}
	}
}

void maintreasureHunt(int row, int col)
{
	Minner firstState(row, col, 0);
	breakMines(firstState);
}

void clearMatrix()
{
	for (int row = 0; row < N; ++row)
	{
		for (int col = 0; col < N; ++col)
		{
			matrixCost[row][col] = -1;
		}
	}
}

int main()
{
	int T = 0;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int test_cases = 0; test_cases < T; ++test_cases)
	{
		cin >> N; //row & col size

		int rowLocation2 = 0;
		int colLocation2 = 0;
		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < N; ++col)
			{
				cin >> matrix[row][col];

				if (matrix[row][col] == 1)
				{
					minesLocation[minesCounter].row = row;
					minesLocation[minesCounter].col = col;
					minesCounter++;
				}

				if (matrix[row][col] == 2)
				{
					rowLocation2 = row;
					colLocation2 = col;
					matrix[row][col] = 0;
				}
			}
		}

		clearMatrix();
		maintreasureHunt(rowLocation2, colLocation2);
		cout << "#" << test_cases << " " << maximumTresuary << '\n';
		maximumTresuary = 0;
	}

	return 0;
}