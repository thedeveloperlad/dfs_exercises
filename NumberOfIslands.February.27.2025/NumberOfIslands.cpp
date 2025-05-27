#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;
/*
	Number of Islands

	Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

    An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.


*/

/*
	00 01 02 {-1,0},{0,1},{1,0},{0,-1}
	10 11 12
	20 21 22
*/
#define MAX 300

int matrix[MAX][MAX];
int N = 0;
int M = 0;
int numberOfIslands = 0;
int deltaCoords[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < M)
		return true;
	return false;
}

struct NumberOfIslands
{
	int row;
	int col;
	int cnt;

	NumberOfIslands(int r, int c, int cn) :
		row(r),
		col(c),
		cnt(cn) {}

};

void dfsNumberOfIslands(NumberOfIslands &state)
{
	matrix[state.row][state.col] = 0;
	for (int delta = 0; delta < 4; ++delta)
	{
		int newRow = state.row + deltaCoords[delta][0];
		int newCol = state.col + deltaCoords[delta][1];

		if (isSafe(newRow, newCol))
		{
			if (matrix[newRow][newCol] == 1)
			{
				NumberOfIslands newState(newRow, newCol, 0);
				dfsNumberOfIslands(newState); // hacer 0 en la recursion
			}
		}
	}
}

void searchIslands()
{
	for (int row = 0; row < N; ++row)
	{
		for (int col = 0; col < M; ++col)
		{
			if (matrix[row][col] == 1)
			{
				NumberOfIslands firstState(row, col, 0);
				dfsNumberOfIslands(firstState); // hacer 0 en la recursion
				numberOfIslands++;
			}
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
		cin >> M; //col size
		cin >> N; //row size

		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < M; ++col)
			{
				cin >> matrix[row][col];
			}
		}

		searchIslands();
		cout << "#" << test_cases << " " << numberOfIslands << '\n';
		numberOfIslands = 0;
	}

	return 0;
}