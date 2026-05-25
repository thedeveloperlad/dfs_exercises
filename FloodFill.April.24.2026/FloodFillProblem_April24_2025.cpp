/*
733. Flood Fill

You are given an image represented by an m x n grid of integers image, where image[i][j] represents the pixel value of the image. 
You are also given three integers sr, sc, and color. 
Your task is to perform a flood fill on the image starting from the pixel image[sr][sc].

To perform a flood fill:

1-. Begin with the starting pixel and change its color to color.

2-. Perform the same process for each pixel that is directly adjacent (pixels that share a side with the original pixel, either horizontally or vertically) and shares the same color as the starting pixel.

3-. Keep repeating this process by checking neighboring pixels of the updated pixels and modifying their color if it matches the original color of the starting pixel.
The process stops when there are no more adjacent pixels of the original color to update.

4-. Return the modified image after performing the flood fill.

source: https://leetcode.com/problems/flood-fill/description/?envType=problem-list-v2&envId=depth-first-search

*/
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

#define N_MAX 10
#define M_MAX 10

int M = 0; // row
int N = 0; // col
int sr = 0;
int sc = 0;
int colour = 0;
int oldColour = 0;
int deltaCoords[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
int matrix[N_MAX][M_MAX]; //main matrix
int finalMatrix[N_MAX][M_MAX]; //print matrix
bool visitedMatrix[N_MAX][M_MAX];

struct FloodFill
{
	int row;
	int col;

	FloodFill(int r, int c) :
		row(r),
		col(c) {}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < M && col >= 0 && col < N)
		return true;
	return false;
}

void dfsFloodFill(FloodFill& state)
{
	for (int delta = 0; delta < 4; ++delta)
	{
		int newRow = state.row + deltaCoords[delta][0];
		int newCol = state.col + deltaCoords[delta][1];

		if (isSafe(newRow, newCol) && matrix[newRow][newCol] == oldColour)
		{
			if (visitedMatrix[newRow][newCol] == false)
			{
				visitedMatrix[newRow][newCol] = true;
				FloodFill newState(newRow, newCol);
				finalMatrix[newRow][newCol] = colour;
				dfsFloodFill(newState);
				visitedMatrix[newRow][newCol] = false;
			}
		}
	}
}

void mainFloodFill(int srow, int scol, int colour) 
{
	FloodFill firstState(srow, scol);
	finalMatrix[srow][scol] = matrix[srow][scol];
	dfsFloodFill(firstState);
}

void printResult(int matrix[N_MAX][M_MAX])
{
	for (int row = 0; row < M; ++row)
	{
		for (int col = 0; col < N; ++col)
		{
			// cin >> matrix[row][col];
			cout << matrix[row][col];
		}
		cout << '\n';
	}
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
		cin >> sr; //s row
		cin >> sc; //s col
		cin >> colour; //colour

		for (int row = 0; row < M; ++row)
		{
			for (int col = 0; col < N; ++col)
			{
				cin >> matrix[row][col];
			}
		}

		oldColour = matrix[sr][sc]; // get old colour to pain new colour
		mainFloodFill(sr, sc, colour);
		cout << "#" << test_cases << '\n';
		printResult(finalMatrix);
		// cout << "#" << test_cases << " " << gPerimeter << '\n';
		//minPath = INT_MAX;
		// clearVars();
		int breaks = 0;
	}

	return 0;
}