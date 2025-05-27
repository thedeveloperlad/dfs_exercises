#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;
/*
	Trekking

	Find the path for which the least energy is requiered for that path.

	starting point (1,1) arrival point (0,0)

	9 5 7 9
	8 4 2 5
	7 6 5 4
	8 8 9 5

*/

/*
	00 01 02 {-1,0},{0,1},{1,0},{0,-1}
	10 11 12
	20 21 22
*/
#define N_MAX 5

int matrix[N_MAX][N_MAX];
int N = 0;
int minimumPath = INT_MAX;
int deltaCoords[2][2] = { {0,1},{1,0} };

struct Trekking
{
	int row;
	int col;
	int cntPath;

	Trekking(int r, int c, int cnt) :
		row(r),
		col(c),
		cntPath(cnt) {}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < N)
	{
		return true;
	}
	return false;
}

void dfsTrekking(Trekking &state)
{
	if (state.row == (N - 1) && state.col == (N - 1))
	{
		if (state.cntPath < minimumPath)
		{
			minimumPath = state.cntPath;
		}
		return;
	}
	else
	{
		for (int coords = 0; coords < 2; ++coords)
		{
			int newRow = state.row + deltaCoords[coords][0];
			int newCol = state.col + deltaCoords[coords][1];

			if (isSafe(newRow, newCol))
			{
				//do the logic
				if (matrix[state.row][state.col] > matrix[newRow][newCol])
				{
					int diff = matrix[state.row][state.col] - matrix[newRow][newCol];
					Trekking newState(newRow, newCol, state.cntPath + diff);
					dfsTrekking(newState);
				}
				else
				{
					int diff = (matrix[newRow][newCol]) - matrix[state.row][state.col];
					Trekking newState(newRow, newCol, state.cntPath + diff + 1);
					dfsTrekking(newState);
				}
			}
		}
	}
}

void mainTrekking(int row, int col)
{
	Trekking firstState(row, col, 0);
	dfsTrekking(firstState);
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

		mainTrekking(0, 0);
		cout << "#" << test_cases << " " << minimumPath << '\n';
		minimumPath = INT_MAX;

	}

	return 0;
}