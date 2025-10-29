#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

/*
	Minimum Path Sum

	Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

	Note: You can only move either down or right at any point in time.

	m == grid.length
	n == grid[i].length
	1 <= m, n <= 200
	0 <= grid[i][j] <= 200

	00 01 02 {-1,-1}, {-1,0}, {-1, 1}
	10 11 12 {0,-1}, {0,0}, {0,1}
	20 21 22 {1,-1}, {1,0}, {1,1}

*/
#define N_MAX 3
#define M_MAX 4
#define L_MAX 15

int M = 0; // row
int N = 0; // col
int matrix[N_MAX][M_MAX]; //main matrix
int deltaCoords[2][2] = { {1,0} , {0,1} };
int minPath = INT_MAX;

struct MinimumPathSum
{
	int row;
	int col;
	int cnt;

	MinimumPathSum(int r, int c, int cn):
		row(r),
		col(c),
		cnt(cn){ }
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < M && col >= 0 && col < N)
		return true;
	return false;
}

void dfsMinimumPathSum(MinimumPathSum &state)
{
	if (state.row == (M-1) && state.col == (N-1))
	{
		if (state.cnt < minPath)
		{
			minPath = state.cnt;
		}
		return;
	}
	else
	{
		for (int delta = 0; delta < 2; ++delta)
		{
			int newRow = state.row + deltaCoords[delta][0];
			int newCol = state.col + deltaCoords[delta][1];

			if (isSafe(newRow, newCol))
			{
				if ((state.cnt + matrix[newRow][newCol]) < minPath)
				{
					MinimumPathSum newState(newRow, newCol, state.cnt + matrix[newRow][newCol]);
					dfsMinimumPathSum(newState);
				}
			}
		}
	}
}

void mainMinimumPathSum(int row, int col)
{
	MinimumPathSum firstState(row, col, matrix[row][col]);
	dfsMinimumPathSum(firstState);
}

int main()
{
	int T = 0;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int test_cases = 0; test_cases < T; ++test_cases)
	{
		//cin >> WORD_LENGTH; // word.length
		cin >> M; //row
		cin >> N; //col
		
		for (int row = 0; row < M; ++row)
		{
			for (int col = 0; col < N; ++col)
			{
				cin >> matrix[row][col];
			}
		}

		mainMinimumPathSum(0,0);
	
		cout << "#" << test_cases << " " << minPath << '\n';
		//clearVars();
		minPath = INT_MAX;
		int breaks = 0;
	}

	return 0;
}