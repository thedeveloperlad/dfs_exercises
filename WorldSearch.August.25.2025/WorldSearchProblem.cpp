#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

/*
	World Search

	Given an m x n grid of characters board and a string word, return true if word exists in the grid.

	The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally
	or vertically neighboring. The same letter cell may not be used more than once.

	m == board.length

	n = board[i].length

	1 <= m, n <= 6

	1 <= word.length <= 15

	board and word consists of only lowercase and uppercase English letters.

	00 01 02 {-1,-1}, {-1,0}, {-1, 1} 
	10 11 12 {0,-1}, {0,0}, {0,1} 
	20 21 22 {1,-1}, {1,0}, {1,1} 

*/
#define N_MAX 3
#define M_MAX 4
#define L_MAX 15

int N = 0;
int M = 5;
int C = 0;
int WORD_LENGTH = 0;
char matrix[N_MAX][M_MAX]; //main matrix
char word[L_MAX];
bool foundSearchWorld = false;
int deltaCoords[8][2] = { {-1,-1}, {-1,0}, {-1, 1} , {0,-1}, {0,1} , {1,-1}, {1,0}, {1,1} };
bool visitedMatrix[N_MAX][M_MAX];
bool letterFound = true;

struct searchWord
{
	int row;
	int col;
	int findLetterCounter;

	searchWord(int r, int c, int cnt) :
		row(r),
		col(c),
		findLetterCounter(cnt) {}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N_MAX && col >= 0 && col < M_MAX)
		return true;
	return false;
}

bool compareChar(char letter1, char letter2)
{
	if (letter1 == letter2)
		return true;
	return false;
}

void clearVars()
{
	foundSearchWorld = false;
	letterFound = true;

	for (int row = 0; row < WORD_LENGTH; ++row)
	{
		word[row] = 0;
	}

	for (int row = 0; row < N_MAX; ++row)
	{
		for (int col = 0; col < M_MAX; ++col)
		{
			matrix[row][col] = 0;
			visitedMatrix[row][col] = 0;
		}
	}
}

void searchWorldDFS(searchWord &state, int letterRow)
{
	if (letterRow == WORD_LENGTH)
	{
		foundSearchWorld = true;
	}

	if ((letterRow < WORD_LENGTH) && foundSearchWorld == false && letterFound == true)
	{
		for (int coords = 0; coords < 8; ++coords)
		{
			int newRow = state.row + deltaCoords[coords][0];
			int newCol = state.col + deltaCoords[coords][1];

			if (isSafe(newRow, newCol))
			{
				//do the algorithm to solve searchWord
				
				char searchChar = word[letterRow];
				char charInMatrix = matrix[newRow][newCol];

				if (visitedMatrix[newRow][newCol] == false)
				{
					if (compareChar(searchChar, charInMatrix))
					{
						visitedMatrix[newRow][newCol] = true;
						matrix[newRow][newCol] = 0;
						searchWord newState(newRow, newCol, state.findLetterCounter + 1);
						searchWorldDFS(newState, letterRow + 1);
					}
					else
					{
						letterFound = false;
						break;
					}
				}
			}
		}
	}
}

void mainSearchWorld(int letterRow)
{
	for (int row = 0; row < N_MAX; ++row)
	{
		for (int col = 0; col < M_MAX; ++col)
		{
			if (word[letterRow] == matrix[row][col])
			{
				// do something
				searchWord firstState(row, col, 1);
				searchWorldDFS(firstState, letterRow+1);

				// do something to break the loop
				if (foundSearchWorld)
					break;
			}
		}
	}
}

int main()
{
	int T = 0;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int test_cases = 0; test_cases < T; ++test_cases)
	{
		cin >> WORD_LENGTH; // word.length
		for (int row = 0; row < WORD_LENGTH; ++row)
		{
			cin >> word[row];
		}

		cin >> N; // row
		cin >> M; // col
		for (int row = 0; row < N; ++row)
		{
			for (int col = 0; col < M; ++col)
			{
				cin >> matrix[row][col];
			}
		}

		for (int letterRow = 0; letterRow < WORD_LENGTH; ++letterRow)
		{
			mainSearchWorld(letterRow);
		}
		
		if (foundSearchWorld)
		{
			cout << "#" << test_cases << " " << "true" << '\n';
		}
		else
		{
			cout << "#" << test_cases << " " << "false" << '\n';
		}

		clearVars();
		int breaks = 0;
	}

	return 0;
}