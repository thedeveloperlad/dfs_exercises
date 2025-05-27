#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;
/*
Consider the below example in which a two-dimensional grid is given 
where each cell contains an integer cost representing the cost to traverse that cell,
we have to find the path from the top-left cell to the bottom-right cell with the minimum total cost.

00 01 02 {{-1,0},{0,1},{1,0},{0,-1}}
10 11 12
20 21 22

*/
#define N_MAX 15

int matrix[N_MAX][N_MAX];
int N = 0;
int minimumCostPath = INT_MAX;
int deltaCoords[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
int costMatrix[N_MAX][N_MAX];

struct Path
{
	int row;
	int col;
	int cnt;

	Path(int r, int c, int counter) :
		row(r),
		col(c),
		cnt(counter) {}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < N)
		return true;
	return false;
}

void clearMatrix()
{
	for (int row = 0; row < N; ++row)
	{
		for (int col = 0; col < N; ++col)
		{
			matrix[row][col] = 0;
			costMatrix[row][col] = INT_MAX;
		}
	}
}

void fillMaxvalueMatrix()
{
	for (int row = 0; row < N; ++row)
	{
		for (int col = 0; col < N; ++col)
		{
			costMatrix[row][col] = INT_MAX;
		}
	}
}

void minimumCostPathDFS(Path &state)
{
	if (state.row == (N - 1) && state.col == (N - 1)) //base case
	{
		if (state.cnt < minimumCostPath)
		{
			minimumCostPath = state.cnt;
		}
	}
	else
	{
		for (int coords = 0; coords < 4; ++coords)
		{
			int newRow = state.row + deltaCoords[coords][0]; //row
			int newCol = state.col + deltaCoords[coords][1]; //col

			if (isSafe(newRow, newCol))
			{
				if ((state.cnt + matrix[newRow][newCol]) < costMatrix[newRow][newCol])
				{
					costMatrix[newRow][newCol] = state.cnt + matrix[newRow][newCol];
					Path newState(newRow, newCol, state.cnt + matrix[newRow][newCol]);
					minimumCostPathDFS(newState);
				}
			}
		}
	}
}

void mainMinimumCostPath()
{
	Path firstState(0, 0, matrix[0][0]);
	minimumCostPathDFS(firstState);
}

int main()
{
	int T = 0;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int test_cases = 0; test_cases < T; ++test_cases)
	{
		cin >> N;
		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < N; ++col)
			{
				cin >> matrix[row][col];
			}
		}

		fillMaxvalueMatrix();
		mainMinimumCostPath();
		cout << "#" << test_cases << " " << minimumCostPath << '\n';
		minimumCostPath = INT_MAX;
		N = 0; //size
		clearMatrix();
	}

	return 0;
}
