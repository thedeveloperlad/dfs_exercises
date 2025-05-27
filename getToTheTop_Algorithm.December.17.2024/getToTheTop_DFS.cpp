#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

/*
	Get to the top

	A monkey enters a room filled with NxM boxes, some boxes are empty and others have a banana.
	The monkey has a mental illness and can only go foward (left, center, right). Help the monkey
	get the max number of bananas

	00 01 02 -1,-1, -1,0, -1, 1
	10 11 12
	20 21 22

*/
#define N_MAX 30
#define M_MAX 30

int maximum_banana = INT_MIN;
int matrix[N_MAX][M_MAX];
int N = 0; //row
int M = 0; //col
int K = 0;
int deltaCoords[3][2] = { {-1,-1}, {-1,0}, {-1, 1} };

struct Monkey
{
	int row;
	int col;
	int bananas;

	Monkey(int r, int c, int cnt) :
		row(r),
		col(c),
		bananas(cnt) {}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < M)
		return true;
	return false;
}

void getToTheTopDFS(Monkey& state)
{
	if (state.row == 0) // top
	{
		if (state.bananas > maximum_banana)
		{
			maximum_banana = state.bananas;
		}
		return;
	}
	else
	{
		for (int coords = 0; coords < 3; ++coords)
		{
			int newRow = state.row + deltaCoords[coords][0];
			int newCol = state.col + deltaCoords[coords][1];

			if (isSafe(newRow, newCol))
			{
				Monkey newState(newRow, newCol, matrix[newRow][newCol] + state.bananas);
				getToTheTopDFS(newState);
			}
		}
	}
}

void mainGetToTheTop(int N, int M)
{
	Monkey firstState(N - 1, K - 1, 0);
	getToTheTopDFS(firstState);
}

int main()
{
	int T = 0;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int test_cases = 0; test_cases < T; ++test_cases)
	{
		cin >> N; // row
		cin >> M; // col
		cin >> K; // monkey start position

		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < M; ++col)
			{
				cin >> matrix[row][col];
			}
		}

		mainGetToTheTop(N, M);
		cout << "#" << test_cases << " " << maximum_banana << '\n';
		maximum_banana = INT_MIN;
		N = 0; //row
		M = 0; //col
		K = 0;
	}

	return 0;
}