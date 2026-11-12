#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

/*
	329. Longest Increasing Path in a Matrix

	Given an m x n integers matrix, return the length of the longest increasing path in matrix.

	From each cell, you can either move in four directions: left, right, up, or down. 
	You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).

	Example 1:

	Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
	Output: 4
	Explanation: The longest increasing path is [1, 2, 6, 9]

	Example 2:

	Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
	Output: 4
	Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
	
	Example 3:

	Input: matrix = [[1]]
	Output: 1

	00 01 02 {-1,-1}, {-1,0}, {-1, 1}
	10 11 12 {0,-1}, {0,0}, {0,1}
	20 21 22 {1,-1}, {1,0}, {1,1}

*/
#define N_MAX 3
#define M_MAX 4
int N = 0; // row
int M = 5; // col
int longestPath = 1;
int matrix[N_MAX][M_MAX]; //main matrix
int deltaCoords[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} };

struct LongestIncreasingPath
{
	int row;
	int col;
	int counter;

	LongestIncreasingPath(int r, int c, int cnt) :
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

void longestIncreasingPathDFS(LongestIncreasingPath& state)
{
	if (state.counter > longestPath)
	{
		longestPath = state.counter;
		return;
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
				if (matrix[newRow][newCol] > actualValue)// && (actualValue+1) == matrix[newRow][newCol])
				{
					LongestIncreasingPath newState(newRow, newCol, state.counter + 1);
					longestIncreasingPathDFS(newState);
				}
			}
		}
	}
}

void mainLongestIncreasingPath(int row, int col)
{
	LongestIncreasingPath firstState(row, col, 1);
	longestIncreasingPathDFS(firstState);
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
				mainLongestIncreasingPath(row, col);
			}
		}

		// print results
		cout << "#" << test_cases << " " << longestPath <<"\n";
		longestPath = 1;
	}

	return 0;
}