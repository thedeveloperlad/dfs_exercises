#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;
/*
	Escape from the Cave

	An expedition team was exploring a new cave. While the team was in the cave, and earthquake ocurred and some parts of the cave became blocked.

	Fortunately. the team has a map that shows the mouth of the cave and the team's current location. They also have three small bombs to blow the blocked areas open.

	S indicates the current location of the expedition team.
	E marks the mouth of the cave and the red-colored cells are the blocked areas.

	Since they are running out of food and water. they have to escape from the cave by blowing out the blocked areas with the three bombs and going to the mouth of the cave in the least amouth of time.

	The team can move in four directions, vertically and horizontally. It takes one hour ro move one cell.

	You are given a map of the cave. Write a program that prints the least amount of time in wich the expedition team can escape from the cave
	by departing from the current location and arriving at the mouth of the cave.

	Constrains:

	1.- The size of a map of the cave is N*N, and N is given as an integer that is greater than or equal to 10 and less than or equal to 30. (10 <= N <= 30)
	2.- There exist only one current location of the expedition team. And the cave has only one mouth.
	3.- The expedition team can move one cell in one hour, they can move in four directions, vertically and horizontally.
	4.- One small bomb can blow one blocked cell open on the map.
	5.- The number of blocked areas that can be blown out using the small bombs is greater than or equal to 3 and less than or equal to 10.
	6.- On the cave map, '0' indicates an area the team can go to and '1' represents a cave wall that the team cannot move to.
	7.- On the cave map, '2' means the blocked areas that can be blown out with the small bombs and '3' shows the current location of the team and '4' denotes the mouth of the cave.
	8.- The edge of the cave map is always '1' and the team cannot go to the area.


*/

/*
	00 01 02 {-1,0},{0,1},{1,0},{0,-1}
	10 11 12
	20 21 22
*/
#define MAX 30

int matrix[MAX][MAX];
int N = 0;
int deltaCoords[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
int locationRow = 0;
int locationCol = 0;
int minimumTimePath = INT_MAX;
int wallsCounter = 0;
int costMatrix[MAX][MAX];
bool visitedMatrix[MAX][MAX];

struct Walls
{
	int row;
	int col;
};

struct EscapeFromTheCave
{
	int row;
	int col;
	int cnt;

	EscapeFromTheCave(int r, int c, int cn) :
		row(r),
		col(c),
		cnt(cn) {}
};

Walls wallsLocations[MAX];

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < N)
		return true;
	return false;
}

void resetCostMatrix()
{
	for (int row = 0; row < N; ++row)
	{
		for (int col = 0; col < N; ++col)
		{
			costMatrix[row][col] = INT_MAX;
		}
	}
}

void mainEscapeFromTheCaveDFS(EscapeFromTheCave &state)
{
	if (matrix[state.row][state.col] == 4)
	{
		if (state.cnt < minimumTimePath)
		{
			minimumTimePath = state.cnt;
		}
		return;
	}
	else
	{
		for (int coords = 0; coords < 4; ++coords)
		{
			int newRow = state.row + deltaCoords[coords][0];
			int newCol = state.col + deltaCoords[coords][1];

			if (isSafe(newRow, newCol))
			{
				if (matrix[newRow][newCol] != 1 && matrix[newRow][newCol] != 2)
				{
					if (state.cnt + 1 < costMatrix[newRow][newCol])
					{
						costMatrix[newRow][newCol] = state.cnt + 1;
						EscapeFromTheCave newState(newRow, newCol, state.cnt + 1);
						mainEscapeFromTheCaveDFS(newState);
						costMatrix[newRow][newCol] = costMatrix[state.row][state.col];
					}
				}
			}
		}
	}
}

void breakWalls(EscapeFromTheCave& state)
{
	for (int x = 0; x < wallsCounter; ++x)
	{
		for (int y = x + 1; y < wallsCounter; ++y)
		{
			for (int z = y; z < wallsCounter; ++z)
			{
				int saveRow1 = wallsLocations[x].row;
				int saveCol1 = wallsLocations[x].col;

				int saveRow2 = wallsLocations[y].row;
				int saveCol2 = wallsLocations[y].col;

				int saveRow3 = wallsLocations[z].row;
				int saveCol3 = wallsLocations[z].col;

				matrix[wallsLocations[x].row][wallsLocations[x].col] = 0;
				matrix[wallsLocations[y].row][wallsLocations[y].col] = 0;
				matrix[wallsLocations[z].row][wallsLocations[z].col] = 0;

				resetCostMatrix();
				mainEscapeFromTheCaveDFS(state);

				matrix[saveRow1][saveCol1] = 2;
				matrix[saveRow2][saveCol2] = 2;
				matrix[saveRow3][saveCol3] = 2;
			}
		}
	}
}

void mainEscapeFromTheCave(int row, int col)
{
	EscapeFromTheCave firstState(row, col, 0);
	breakWalls(firstState);
}

int main()
{
	int T = 0;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int test_cases = 0; test_cases < T; ++test_cases)
	{
		cin >> N; //row & col size

		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < N; ++col)
			{
				cin >> matrix[row][col];

				if (matrix[row][col] == 3)
				{
					locationRow = row;
					locationCol = col;
				}

				if (matrix[row][col] == 2) //wall
				{
					wallsLocations[wallsCounter].row = row;
					wallsLocations[wallsCounter].col = col;
					wallsCounter++;
				}
			}
		}

		mainEscapeFromTheCave(locationRow, locationCol);

		if (minimumTimePath == 2147483647)
		{
			minimumTimePath = -1;
		}

		cout << "#" << test_cases << " " << minimumTimePath << '\n';
		minimumTimePath = 0;
		wallsCounter = 0;
	}

	return 0;
}