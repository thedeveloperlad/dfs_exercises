/*
Problem: Longest Increasing Path in a Matrix

link: https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/

Problem Description

Given an m x n integers matrix, return the length of the longest increasing path in matrix.

From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally 
or move outside the boundary (i.e., wrap-around is not allowed).

Examples:

Example 1
Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].

Example 2
Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.

Example 3:

Input: matrix = [[1]]
Output: 1

*/
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

#define N_MAX 12

int N = 0;
int M = 0;
char matrix[N_MAX][N_MAX];
int longestPath = 0;
int deltaCoords[4][2] = { {-1, 0}, {0, 1}, {1,0}, {0,-1} }; // To move 4 places

/*
00 01 02 {{-1, 0}, {0, 1}, {1,0}, {0,-1}}
10 11 12
20 21 22
*/

struct LongestPath
{
	int row;
	int col;
	int counter;

	LongestPath(int r, int c, int cnt) :
		row(r),
		col(c),
		counter(cnt) {}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < M)
		return true;
	return false;
}

void dfsLongestIncreasingPath(LongestPath& state)
{
	if (state.counter > longestPath)
	{
		longestPath = state.counter;
	}
	
	for (int delta = 0; delta < 4; ++delta)
	{
		int newRow = state.row + deltaCoords[delta][0];
		int newCol = state.col + deltaCoords[delta][1];

		if (isSafe(newRow, newCol))
		{
			if (matrix[state.row][state.col] > matrix[newRow][newCol]) // check if the next step is highest to continue.
			{
				LongestPath newState(newRow, newCol, state.counter+1);
				dfsLongestIncreasingPath(newState);
			}
		}
	}
}

void mainLongestIncreasingPath(int row, int col)
{
	LongestPath firstState(row, col, 1);
	dfsLongestIncreasingPath(firstState);
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

		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < M; ++col)
			{
				mainLongestIncreasingPath(row, col); //starting point
			}
		}
		
		cout << "#" << test_cases << " " << longestPath << '\n';
		longestPath = 0;

	}

	return 0;
}