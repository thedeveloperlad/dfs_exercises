#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;
/*
	Street Light

	You are trying to walk home at dark night, But you will only use the streets that are illuminated by
	the streetlights.

	You are given a two dimensional map represented by a rectangular grid with height H and width W. On the
	map, a street is valued as 0, as well is valued as 1 and a place where a street

*/

/*
	00 01 02 {-1,0},{0,1},{1,0},{0,-1}
	10 11 12
	20 21 22
*/
#define N_MAX 10
#define M_MAX 10

int matrix[N_MAX][M_MAX];
int N = 0;
int M = 0;
int maxWays = 0;
int deltaCoords[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
int matrixWithLights[N_MAX][M_MAX];
bool visitedMatrix[N_MAX][M_MAX];

struct StreetLight
{
	int row;
	int col;
	int cnt;

	StreetLight(int r, int c, int cn) :
		row(r),
		col(c),
		cnt(cn) {}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < M)
		return true;
	return false;
}

void dfsStreetLight(StreetLight &state)
{
	// visitedMatrix[state.row][state.col] = true;
	if (state.row == (N - 1) && state.col == (M - 1))
	{
		maxWays++;
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
				if (matrixWithLights[newRow][newCol] == 2 && visitedMatrix[newRow][newCol] == false)
				{
					visitedMatrix[newRow][newCol] = true;
					StreetLight newState(newRow, newCol, state.cnt+1);
					dfsStreetLight(newState);
					visitedMatrix[newRow][newCol] = false;
				}
			}
		}
	}
	// visitedMatrix[state.row][state.col] = false;
}

void paint2Map(int row, int col)
{
	matrixWithLights[row][col] = 2; // light
	for (int coords = 0; coords < 4; ++coords)
	{
		for (int potencia = 0; potencia < 10; ++potencia)
		{
			int newRow = row + deltaCoords[coords][0]*potencia;
			int newCol = col + deltaCoords[coords][1]*potencia;

			if (isSafe(newRow, newCol))
			{
				if (matrix[newRow][newCol] == 1)
				{
					break;
				}
				else if(matrix[newRow][newCol] == 0)
				{
					matrixWithLights[newRow][newCol] = 2;
				}
			}
		}
	}
	return;
}

void fillLights()
{
	for (int row = 0; row < N; ++row)
	{
		for (int col = 0; col < M; ++col)
		{
			if (matrix[row][col] == 2)
			{
				//paint of 2 row and col.
				paint2Map(row, col);
			}
		}
	}
}

void clearMap()
{
	for (int row = 0; row < N; ++row)
	{
		for (int col = 0; col < M; ++col)
		{
			matrix[row][col] = 0;
			visitedMatrix[row][col] = false;
			matrixWithLights[row][col] = 0;
		}
	}
}

void mainStreetLight(int row, int col)
{
	fillLights();
	StreetLight firstState(row, col, 0);
	dfsStreetLight(firstState);
}

int main()
{
	int T = 0;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int test_cases = 0; test_cases < T; ++test_cases)
	{
		cin >> N; //row
		cin >> M; // col
		
		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < M; ++col)
			{
				cin >> matrix[row][col];
			}
		}

		mainStreetLight(0, 0);
		cout << "#" << test_cases << " " << maxWays << '\n';
		maxWays = 0;
		clearMap();

	}

	return 0;
}