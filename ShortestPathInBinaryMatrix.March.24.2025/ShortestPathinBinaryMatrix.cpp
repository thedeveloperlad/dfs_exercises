#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;
/*
	Shortest Path in Binary Matrix

Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.

A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

All the visited cells of the path are 0.
All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
The length of a clear path is the number of visited cells of this path.

*/

/*
	00 01 02 {-1,0},{0,1},{1,0},{0,-1}
	10 11 12
	20 21 22

	00 01 02 {-1,-1}, {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}
	10 11 12
	20 21 22
*/
#define MAX 30

int matrix[MAX][MAX];
int N = 0;
int deltaCoords[8][2] = { {-1,-1}, {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1} };
int minimumPath = INT_MAX;
int costMatrix[MAX][MAX];
bool visitedMatrix[MAX][MAX];

struct FindPath
{
	int row;
	int col;
	int cnt;

	FindPath(int r, int c, int cn) :
		row(r),
		col(c),
		cnt(cn) {}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < N)
		return true;
	return false;
}

void dfsShortestPathBinaryMatrix(FindPath& state)
{
	if (state.row == (N-1) && state.col == (N - 1))
	{
		if (state.cnt < minimumPath)
		{
			minimumPath = state.cnt;
		}
		return;
	}
	else
	{
		for (int delta = 0; delta < 8; ++delta)
		{
			int newRow = state.row + deltaCoords[delta][0];
			int newCol = state.col + deltaCoords[delta][1];

			if (isSafe(newRow, newCol))
			{
				if (matrix[newRow][newCol] == 0)
				{
					if(visitedMatrix[newRow][newCol] == false)
					{
						visitedMatrix[newRow][newCol] = true;
						FindPath newState(newRow, newCol, state.cnt + 1);
						dfsShortestPathBinaryMatrix(newState);
						visitedMatrix[newRow][newCol] = false;
					}
				}
			}

		}
	}
}

void mainShortestPathBinaryMatrix(int row, int col)
{
	FindPath firstState(row, col, 1);
	dfsShortestPathBinaryMatrix(firstState);
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

		mainShortestPathBinaryMatrix(0, 0);
		cout << "#" << test_cases << " " << minimumPath << '\n';
		minimumPath = INT_MAX;

	}

	return 0;
}