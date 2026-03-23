#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

/*
	Island Perimeter

	You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.

	Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, 
	and there is exactly one island (i.e., one or more connected land cells).

	The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. 
	One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. 
	Determine the perimeter of the island.

	Example 1:

		Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
	
		Output: 16
	
	Explanation: The perimeter is the 16 yellow stripes in the image above.

	Example 2:

		Input: grid = [[1]]
		Output: 4
		Example 3:

		Input: grid = [[1,0]]
		Output: 4

	Constraints:

		row == grid.length
		col == grid[i].length
		1 <= row, col <= 100
		grid[i][j] is 0 or 1.
		There is exactly one island in grid.

	00 01 02 {-1,0},{0,1},{1,0},{0,-1}
	10 11 12
	20 21 22

*/
#define N_MAX 10
#define M_MAX 10

int M = 0; // row
int N = 0; // col
int matrix[N_MAX][M_MAX]; //main matrix
int matrixNumbers[N_MAX][M_MAX]; //main matrix
int deltaCoords[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
bool visitedMatrix[N_MAX][M_MAX];
int testAddArray[N_MAX];
int testAddCounter = 0;
int gPerimeter = 0;

struct IslandPerimeter
{
	int row;
	int col;
	int counter;

	IslandPerimeter(int r, int c, int cnt) :
		row(r),
		col(c),
		counter(cnt) {}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < M && col >= 0 && col < N)
		return true;
	return false;
}

int checkPerimeter(int row, int col)
{
	int counter = 0;
	for (int delta = 0; delta < 4; ++delta)
	{
		int newRow = row + deltaCoords[delta][0];
		int newCol = col + deltaCoords[delta][1];

		if (matrix[newRow][newCol] == 0 || isSafe(newRow, newCol) == false)
		{
			counter++;
		}
	}

	testAddArray[testAddCounter] = counter;
	testAddCounter++;
	return counter; // return value
}

int perimeter(int row, int col)
{
	int totalPerimeter = 0;

	for (int row = 0; row < M; ++row)
	{
		for (int col = 0; col < N; ++col)
		{
			if (matrix[row][col] == 1)
			{
				totalPerimeter += checkPerimeter(row, col);
			}
		}
	}

	return totalPerimeter;
}

void clearVars()
{
	for (int row = 0; row < N_MAX; ++row)
	{
		for (int col = 0; col < M_MAX; ++col)
		{
			matrix[row][col] = 0;
			visitedMatrix[row][col] = false;
		}
	}
}

void dfsIslandPerimeter(IslandPerimeter &state)
{
	//gPerimeter = state.counter;
	//matrixNumbers[state.row][state.col] = checkPerimeter(state.row, state.col);
	//gPerimeter = gPerimeter + matrixNumbers[state.row][state.col];
	for (int delta = 0; delta < 4; ++delta)
	{
		int newRow = state.row + deltaCoords[delta][0];
		int newCol = state.col + deltaCoords[delta][1];

		if (isSafe(newRow, newCol))
		{
			if (matrix[newRow][newCol] == 1)
			{
				if (visitedMatrix[newRow][newCol] == false)
				{
					visitedMatrix[newRow][newCol] = true;
					//state.counter += checkPerimeter(newRow, newCol);
					//matrix[newRow][newCol] = checkPerimeter(newRow, newCol);
					//gPerimeter += checkPerimeter(newRow, newCol);
					//matrix[newRow][newCol] = 0;
					matrixNumbers[state.row][state.col] = checkPerimeter(state.row, state.col);
					gPerimeter = gPerimeter + matrixNumbers[state.row][state.col];
					IslandPerimeter newState(newRow, newCol, state.counter);
					dfsIslandPerimeter(newState);
					visitedMatrix[newRow][newCol] = false;
				}
			}
		}
	}
}

void mainIslandPerimeter(int row, int col)
{
	//gPerimeter = checkPerimeter(row, col);
	//gPerimeter = perimeter(row, col);
	IslandPerimeter firstState(row, col, 0);
	dfsIslandPerimeter(firstState);
	/*if (N == 1 && M == 1)
	{
		gPerimeter = checkPerimeter(row, col);
	} 
	else
	{
		//gPerimeter = checkPerimeter(row, col);
		IslandPerimeter firstState(row, col, gPerimeter);
		dfsIslandPerimeter(firstState);
	}*/
	/*for (int row = 0; row < M; ++row)
	{
		for (int col = 0; col < N; ++col)
		{
			if (matrix[row][col] == 1)
			{
				//mainIslandPerimeter(row, col);
				//break;
				int number = checkPerimeter(row, col);
				gPerimeter += number;
				matrixNumbers[row][col] = number;
				//gPerimeter += checkPerimeter(row, col);
			}
		}
	}*/

	int breaks = 0;
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

		for (int row = 0; row < M; ++row)
		{
			for (int col = 0; col < N; ++col)
			{
				cin >> matrix[row][col];
			}
		}

		//find 1
		for (int row = 0; row < M; ++row)
		{
			for (int col = 0; col < N; ++col)
			{
				if (matrix[row][col] == 1)
				{
					mainIslandPerimeter(row, col);
					break;
				}
			}
		}

		//mainIslandPerimeter(0, 1);
		cout << "#" << test_cases << " " << gPerimeter << '\n';
		//minPath = INT_MAX;
		gPerimeter = 0;
		clearVars();
		int breaks = 0;
	}

	return 0;
}