#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

/*
	695. Max Area of Island

	You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally
	(horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

	The area of an island is the number of cells with a value 1 in the island.

	Return the maximum area of an island in grid. If there is no island, return 0.

	
	00 01 02 {-1,-1}, {-1,0}, {-1, 1}
	10 11 12 {0,-1}, {0,0}, {0,1}
	20 21 22 {1,-1}, {1,0}, {1,1}

*/
#define N_MAX 12
#define M_MAX 12
#define ISLAND 1
int N = 0; // row
int M = 5; // col
int maximumArea = 0;
int matrix[N_MAX][M_MAX]; //main matrix
int deltaCoords[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} };

struct Island
{
	int row;
	int col;
	int counter;

	Island(int r, int c, int cnt) :
		row(r),
		col(c),
		counter(cnt) {
	}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N_MAX && col >= 0 && col < M_MAX)
		return true;
	return false;
}

void maxAreaofIslandDFS(Island& state)
{
	if (state.counter > maximumArea)
	{
		maximumArea = state.counter;
	}
	else
	{
		for (int delta = 0; delta < 4; ++delta)
		{
			int newRow = state.row + deltaCoords[delta][0];
			int newCol = state.col + deltaCoords[delta][1];

			if (isSafe(newRow, newCol))
			{
				int actualValue = matrix[state.row][state.col];
				if (matrix[newRow][newCol] == ISLAND) // Island found
				{
					matrix[state.row][state.col] = 0;
					Island newState(newRow, newCol, state.counter + 1);
					maxAreaofIslandDFS(newState);
				}
			}
		}
	}
}

void mainMaxAreaofIsland(int row, int col)
{
	Island firstState(row, col, 1);
	maxAreaofIslandDFS(firstState);
}

int main()
{
	int T = 0;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int test_cases = 0; test_cases < T; ++test_cases)
	{
		cin >> N; // row
		cin >> M; // col
		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < M; ++col)
			{
				cin >> matrix[row][col];
			}
		}

		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < M; ++col)
			{
				if (matrix[row][col] == ISLAND)
				{
					mainMaxAreaofIsland(row, col);
				}
			}
		}

		// print results
		cout << "#" << test_cases << " " << maximumArea << "\n";
		maximumArea = 0;
	}

	return 0;
}