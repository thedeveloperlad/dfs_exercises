#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

/*
	79. Word Search

	Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. 
The same letter cell may not be used more than once.

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true

link: https://leetcode.com/problems/word-search/description/
*/
#define N_MAX 12
#define M_MAX 5

int N = 0;
int M = 0;
int matrix[N_MAX][M_MAX]; //main matrix
int deltaCoords[3][2] = { {-1,-1}, {-1,0}, {-1, 1} };


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

		
		//cout << "#" << test_cases << " " << maximumCoins << '\n';
		//maximumCoins = 0;
	}

	return 0;
}