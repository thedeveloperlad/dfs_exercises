/*
Problem: Number of Islands

link: https://www.geeksforgeeks.org/dsa/find-the-number-of-islands-using-dfs/

Problem Description

Given an n × m grid[][] consisting of 'L' (land) and 'W' (water), we need to count the total number of islands present
in the grid without modifying the original grid.

An island is defined as a group of connected 'L' cells that are adjacent horizontally, vertically, or diagonally, 
and surrounded by water or the boundary of the grid.

Examples:

Input: grid[][] = [['L', 'L', 'W', 'W', 'W'],
                            ['W', 'L', 'W', 'W', 'L'],
                           ['L', 'W', 'W', 'L', 'L'],
                          ['W', 'W', 'W', 'W', 'W'],
                         ['L', 'W', 'L', 'L', 'W']]
Output: 4

Input: grid[][] = [['W', 'L', 'L', 'L', 'W', 'W', 'W'],
                            ['W', 'W', 'L', 'L', 'W', 'L', 'W']]
Output: 2

*/
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

#define N_MAX 12

int N = 0;
int M = 0;
char matrix[N_MAX][N_MAX];
int numberOfIslands = 0;
int deltaCoords[8][2] = { {-1,-1}, {-1, 0}, {-1,1}, {0, 1}, {1,1}, {1,0}, {1,-1}, {0,-1} }; // To move 8 places

/*
00 01 02 {{-1,-1}, {-1, 0}, {-1,1}, {0, 1}, {1,1}, {1,0}, {1,-1}, {0,-1}}
10 11 12
20 21 22
*/

struct Islands
{
	int row;
	int col;
	int cnt = 0;

	Islands(int r, int c, int cn):
		row(r),
		col(c),
		cnt(cn){ }
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < M)
		return true;
	return false;
}

void dfsNumberOfIslands(Islands &state)
{
	for (int delta = 0; delta < 8; ++delta)
	{
		int newRow = state.row + deltaCoords[delta][0]; // new row
		int newCol = state.col + deltaCoords[delta][1]; // new col

		if (isSafe(newRow, newCol))
		{
			if (matrix[newRow][newCol] == 'L')
			{
				matrix[newRow][newCol] = 'M'; //visited
				Islands newState(newRow, newCol, 0);
				dfsNumberOfIslands(newState);
			}
		}
	}
}

void mainNumberOfIslands()
{
	for (int row = 0; row < N; ++row)
	{
		for (int col = 0; col < M; ++col)
		{
			if(matrix[row][col] == 'L') // find island.
			{
				numberOfIslands++; //increase the island counter and enter to DFS
				Islands firstState(row, col, 0);
				dfsNumberOfIslands(firstState);
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
		cin >> N;
		cin >> M;
		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < M; ++col)
			{
				cin >> matrix[row][col];
			}
		}

		mainNumberOfIslands();
		cout << "#" << test_cases << " " << numberOfIslands << '\n';
		numberOfIslands = 0;
		
	}

	return 0;
}