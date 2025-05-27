#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;
/*
	Rock Climbing

	Mr. K has a mania for rock-climbing.
	Mr. K who completed several rock-climbing courses in the past now wants to go for a course which is
	known to be tough and hard.

	Given the map of the climbing course, the starting point and goal point, write a program that computes the
	level of difficulty of the rock.

*/

/*
	00 01 02 {-1,0},{0,1},{1,0},{0,-1}
	10 11 12
	20 21 22
*/

#define N_MAX 50
#define M_MAX 50
#define G_POINT 3
#define S_POINT 2
#define GROUND 1

int N = 0;
int M = 0;
int matrix[N_MAX][M_MAX];
int rowG = 0;
int colG = 0;
int rowS = 0;
int colS = 0;
int levelDifficulty = 0;
bool foundGpoint = false;

int deltaCoords[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
bool visitedMatrix[N_MAX][M_MAX];

struct RockClimbing
{
	int row;
	int col;
	int difficulty;

	RockClimbing(int r, int c, int dif) :
		row(r),
		col(c),
		difficulty(dif) {}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < M)
		return true;
	return false;
}

void dfsRockClimbing(RockClimbing &state)
{
	if (state.row == rowG && state.col == colG)
	{
		levelDifficulty = state.difficulty;
		//we need a flag to stop DFS
		foundGpoint = true;
		return;
	}
	else
	{
		if (foundGpoint == false)
		{
			for (int coords = 0; coords < 4; ++coords)
			{
				for (int difficulty = 0; difficulty <= state.difficulty; difficulty++)
				{
					int newRow = state.row + (deltaCoords[coords][0] * difficulty);
					int newCol = state.col + deltaCoords[coords][1];

					if (isSafe(newRow, newCol))
					{
						//do something.
						if (matrix[newRow][newCol] == GROUND && visitedMatrix[newRow][newCol] == false)
						{
							visitedMatrix[newRow][newCol] = true;
							RockClimbing newState(newRow, newCol, state.difficulty);
							dfsRockClimbing(newState);
							visitedMatrix[newRow][newCol] = false;
						}
					}
				}
			}
		}
	}
}

void clear()
{
	rowG = 0;
	colG = 0;
	rowS = 0;
	colS = 0;
	levelDifficulty = 0;
	foundGpoint = false;
}

void mainRockClimbing(int row, int col)
{
	matrix[rowG][colG] = 1;
	for (int difficulty = 0; difficulty < N; difficulty++)
	{
		RockClimbing firstState(row, col, difficulty);
		dfsRockClimbing(firstState);

		if (foundGpoint == true)
			return;
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

				if (matrix[row][col] == G_POINT)
				{
					rowG = row;
					colG = col;
				}

				if (matrix[row][col] == S_POINT)
				{
					rowS = row;
					colS = col;
				}
			}
		}

		mainRockClimbing(rowS, colS);
		cout << "#" << test_cases << " " << levelDifficulty << '\n';
		clear();
	}

	return 0;
}