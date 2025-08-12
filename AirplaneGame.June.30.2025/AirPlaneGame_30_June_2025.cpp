#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

/*
	Aeroplane Bombing

		You’ll be given a grid as below:

					   0 1 0 2 0
					   0 2 2 2 1
					   0 2 1 1 1
					   1 0 1 0 0
					   0 0 1 2 2
					   1 1 0 0 1
					   x x S x x

		In the grid above, 1: This cell has a coin. 2: This cell has an enemy. 0: It contains nothing. 
		The highlighted(yellow) zone is the control zone. S is a spaceship that we need to control so that
		we can get maximum coins. Now, S’s initial position will be at the center and we can only move it right
		or left by one cell or do not move. At each time, the non-highlighted part of the grid will move down
		by one unit. We can also use a bomb but only once. If we use that, all the enemies in the 5×5 region
		above the control zone will be killed. If we use a bomb at the very beginning, the grid will look like this:

					   0 1 0 2 0
					   0 0 0 0 1
					   0 0 1 1 1
					   1 0 1 0 0
					   0 0 1 0 0
					   1 1 0 0 1
					   x x S x x
		
		As soon as, the spaceship encounters an enemy or the entire grid has come down, the game ends. 
		For example, At the very first instance, if we want to collect a coin we should move left( coins=1). 
		This is because when the grid comes down by 1 unit we have a coin on the second position and by moving 
		left we can collect that coin. Next, we should move right to collect another coin( coins=2). After this, 
		remain at the same position( coins=4). This is the current situation after collecting 4 coins.

		0 1 0 2 0 0 1 0 0 0 0 2 2 2 1 -->
		
		after using 0 0 0 0 1 x x S x x -->bomb x x S x x Now, we can use the bomb to get out of this situation. After this, we can collect at most 1 coin. So maximum coins=5.

		
		00 01 02 {-1,-1}, {-1,0}, {-1, 1}
		10 11 12
		20 21 22

*/
#define N_MAX 12
#define M_MAX 5

int N = 0;
int M = 5;
int matrix[N_MAX][M_MAX]; //main matrix
int deltaCoords[3][2] = { {-1,-1}, {-1,0}, {-1, 1} };
int maximumCoins = 0;
int matrixWithoutBombs[N_MAX][M_MAX]; // copy matrix

struct AirPlane
{
	int row;
	int col;
	int coins;

	AirPlane(int r, int c, int cnt) :
		row(r),
		col(c),
		coins(cnt) {}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < M)
		return true;
	return false;
}

void clearMap()
{
	for (int row = 0; row < N; ++row)
	{
		for (int col = 0; col < M; ++col)
		{
			matrixWithoutBombs[row][col] = 0;
		}
	}
}

void dropBomb(int dropBombInRow)
{
	int top = dropBombInRow;
	int end = dropBombInRow - 5;

	if (end <=0 )
	{
		end = 0;
	}

	for (int row = N - 1; row >= 0; --row)
	{
		for (int col = 0; col < M; ++col)
		{
			if ((row <= top && row > end) && (matrix[row][col] == 2))
			{
				matrixWithoutBombs[row][col] = 0; // disable bombs
			}
			else
			{
				matrixWithoutBombs[row][col] = matrix[row][col];
			}
		}
	}
}

void DFSAirPlaneGame(AirPlane &state)
{
	if (matrixWithoutBombs[state.row][state.col] == 1)
	{
		matrixWithoutBombs[state.row][state.col] = 0;
		state.coins = state.coins + 1;
	}
	else if (matrixWithoutBombs[state.row][state.col] == 2)
	{
		state.coins = state.coins - 1;
	}

	if (state.row == 0)
	{
		if (state.coins > maximumCoins)
		{
			maximumCoins = state.coins;
		}
		return;
	}
	else
	{
		for (int delta = 0; delta < 3; ++delta)
		{
			int newRow = state.row + deltaCoords[delta][0];
			int newCol = state.col + deltaCoords[delta][1];

			if (isSafe(newRow, newCol))
			{
				// matrixWithoutBombs[newRow][newCol] = 0;
				AirPlane newState(newRow, newCol, state.coins);
				DFSAirPlaneGame(newState);
			}
		}
	}
}

void mainAirPlaneGame(int row, int col, int rowToDropTheBomb)
{
	AirPlane firstState(row, col, 0);
	dropBomb(rowToDropTheBomb);
	// clearMap();
	DFSAirPlaneGame(firstState);
}

int main()
{
	int T = 0;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int test_cases = 0; test_cases < T; ++test_cases)
	{
		cin >> N; // row

		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < M; ++col)
			{
				cin >> matrix[row][col];
			}
		}

		for (int dropBomb = N - 1; dropBomb >= 0; dropBomb--) //Row to drop the bomb
		{
			clearMap();
			mainAirPlaneGame(N, M, dropBomb);
		}
		cout << "#" << test_cases << " " << maximumCoins << '\n';
		maximumCoins = 0;
	}

	return 0;
}
