#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

/*
	212. Word Search II

	Given an m x n board of characters and a list of strings words, return all words on the board.

	Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally
	or vertically neighboring. The same letter cell may not be used more than once in a word.

	Input: 
	board = 
	[["o","a","a","n"],
	["e","t","a","e"],
	["i","h","k","r"],
	["i","f","l","v"]], 
	
	words = ["oath","pea","eat","rain"]
	
	Output: ["eat","oath"]

	Input: 
	
	board = 
	[["a","b"],
	["c","d"]], 

	words = ["abcb"]
	Output: []

	00 01 02 {-1,-1}, {-1,0}, {-1, 1}
	10 11 12 {0,-1}, {0,0}, {0,1}
	20 21 22 {1,-1}, {1,0}, {1,1}

*/
#define N_MAX 3
#define M_MAX 4
#define L_MAX 15
#define W_MAX 10
int N = 0; // row
int M = 5; // col
int wordsCases = 0;
char matrix[N_MAX][M_MAX]; //main matrix
int deltaCoords[4][2] = { {-1,0}, {0,-1}, {1,0}, {0,1} };
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
		findLetterCounter(cnt) {
	}
};

struct Words
{
	char words[L_MAX];
	int wordLength;
	bool foundWord;
};

Words wordsToFind[W_MAX];

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
	letterFound = true;

	for (int row = 0; row < N_MAX; ++row)
	{
		for (int col = 0; col < M_MAX; ++col)
		{
			matrix[row][col] = 0;
			visitedMatrix[row][col] = 0;
		}
	}
}

void searchWorldDFS(searchWord& state, int wordRow, int letterRow)
{

	if (wordsToFind[wordRow].wordLength == letterRow)
	{
		wordsToFind[wordRow].foundWord = true;
	}

	if (wordsToFind[wordRow].foundWord == false)
	{
		for (int delta = 0; delta < 4; ++delta)
		{
			int newRow = state.row + deltaCoords[delta][0];
			int newCol = state.col + deltaCoords[delta][1];

			if (isSafe(newRow, newCol))
			{
				if (matrix[newRow][newCol] == wordsToFind[wordRow].words[letterRow])
				{
					searchWord newState(newRow, newCol, letterRow + 1);
					searchWorldDFS(newState, wordRow, letterRow + 1);
				}
			}
		}
	}
}

void mainSearchWorld(int wordRow)
{
	for (int row = 0; row < N_MAX; ++row)
	{
		for (int col = 0; col < M_MAX; ++col)
		{
			if (wordsToFind[wordRow].words[0] == matrix[row][col])
			{
				// do something
				searchWord firstState(row, col, 1);
				searchWorldDFS(firstState, wordRow,1);
				
				// do something to break the loop
				if (wordsToFind[wordRow].foundWord)
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
		cin >> wordsCases;
		for (int wordsRow = 0; wordsRow < wordsCases; ++wordsRow)
		{
			cin >> wordsToFind[wordsRow].wordLength;
			for (int row = 0; row < wordsToFind[wordsRow].wordLength; ++row)
			{
				cin >> wordsToFind[wordsRow].words[row];
			}
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

		for (int wordRow = 0; wordRow < wordsCases; ++wordRow)
		{
			mainSearchWorld(wordRow);
		}

		// print results
		cout << "#" << test_cases << " ";
		for (int row = 0; row < wordsCases; ++row)
		{
			if (wordsToFind[row].foundWord)
			{
				for (int letter=0; letter<wordsToFind[row].wordLength; ++letter)
				{
					cout << wordsToFind[row].words[letter];
				}
			}
			cout << " ";
		}
		cout << '\n';
		clearVars();
		int breaks = 0;
	}

	return 0;
}