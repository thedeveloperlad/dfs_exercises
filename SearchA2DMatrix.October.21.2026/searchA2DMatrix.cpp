/*
Problem: 74. Search a 2D Matrix

link: https://leetcode.com/problems/search-a-2d-matrix/description/?envType=problem-list-v2&envId=array

Problem Description

You are given an m x n integer matrix matrix with the following two properties:

Each row is sorted in non-decreasing order.
The first integer of each row is greater than the last integer of the previous row.
Given an integer target, return true if target is in matrix or false otherwise.

You must write a solution in O(log(m * n)) time complexity.

*/
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

#define N_MAX 12

int N = 0;
int M = 0;
int target = 0;
bool targetFound = false;
int matrix[N_MAX][N_MAX];
int deltaCoords[4][2] = { {-1, 0}, {0, 1}, {1,0}, {0,-1} }; // To move 4 places

/*
00 01 02 {{-1, 0}, {0, 1}, {1,0}, {0,-1}}
10 11 12
20 21 22
*/

struct SearchA2D
{
	int row;
	int col;
	bool target;

	SearchA2D(int r, int c, bool trg) :
		row(r),
		col(c),
		target(trg) {
	}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < M)
		return true;
	return false;
}

void dfsSearchInMatrix(SearchA2D &state)
{
	if (matrix[state.row][state.col] == target)
	{
		targetFound = true;
	}
	else
	{
		if (targetFound == false)
		{
			int newCol = state.col + 1;
			
			if (isSafe(state.row, newCol))
			{
				int valueCheck = matrix[state.row][newCol];
				if (valueCheck == target)
				{
					targetFound = true;
				}

				SearchA2D newState(state.row, newCol, targetFound);
				dfsSearchInMatrix(newState);
			}
		}
	}
}

void mainSearchA2D(int row, int col)
{

	SearchA2D firstState(row, col, false);
	dfsSearchInMatrix(firstState);
}

bool searchInMatrix(int target) // brute force
{
	for (int row = 0; row < N; ++row)
	{
		for (int col = 0; col < M; ++col)
		{
			if (target == matrix[row][col])
			{
				return true;
			}
		}
	}
	return false;
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
		cin >> target;

		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < M; ++col)
			{
				cin >> matrix[row][col];
			}
		}

		for (int row = 0; row < N; ++row) //steps
		{
			mainSearchA2D(row, 0);
		}

		if (targetFound == true)
		{
			std::cout << "#" << test_cases << " " << "true" << '\n';
		}
		else
		{
			std::cout << "#" << test_cases << " " << "false" << '\n';
		}
		targetFound = false;

	}

	return 0;
}