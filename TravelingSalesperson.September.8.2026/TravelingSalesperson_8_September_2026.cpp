/*
Problem: Mr. Lee's International Travels (Traveling Salesperson)

Problem Description

Mr. Lee works as an international consultant and must travel from the main headquarters
to various branches abroad to provide technical assistance.There are a total of N offices, numbered from 1 to N. 

The main headquarters (where Mr. Lee starts and ends his journey) is Office No. 1. 

Mr. Lee must plan an itinerary that meets the following conditions:

1-. He must begin his journey at Office No. 1.

2-. He must visit exactly once each of the other N-1 offices.

3-. Upon finishing, he must return directly to Office No. 1.

4-. The total cost of the plane tickets must be the minimum possible.

You will be given an N × N cost matrix, where the value at row i and column j represents 
the price of the flight ticket to travel directly from office i to office j. 

A cost of 0 means that no direct flight exists between those two offices.

Your task is to find the minimum total expense to complete the round trip under these conditions.

Input Format

The first line contains the number of test cases, T.
For each test case:

- The first line contains an integer N, representing the number of offices.
- The next N lines contain N space-separated integers each, representing the flight cost matrix.

Output Format

- For each test case, print a single line in the format Case #X: Y, where X is the test case 
number (starting from 1) and Y is the minimum total cost of the trip.

Constraints

1 ≤ T ≤ 102 ≤ N ≤ 12

The cost of any existing flight is between 1 and 100,000.
The cost of the main diagonal (traveling from an office to itself, where i = j) is always 0.
The test cases are guaranteed to have at least one valid path that connects all offices back to No. 1.

*/
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

#define N_MAX 12

int matrix[N_MAX][N_MAX];
int costMatrix[N_MAX][N_MAX];
int N = 0;

int minCostPath = INT_MAX;
int deltaCoords[4][2] = { {-1, 0}, {0, 1}, {1,0}, {0,-1} };

/*
00 01 01 {-1, 0}, {0, 1}, {1,0}, {0,-1}
10 11 12
20 21 22
*/

struct TravelingSalesperson
{
	int row;
	int col;
	int counter;

	TravelingSalesperson(int r, int c, int cnt) :
		row(r),
		col(c),
		counter(cnt) {
	}
};

bool isSafe(int row, int col)
{
	if (row >= 0 && row < N && col >= 0 && col < N)
		return true;
	return false;
}

void dfsTravelingSalesperson(TravelingSalesperson &state)
{
	/*if (state.counter + matrix[state.row][state.col] < minCostPath)
	{
		minCostPath = state.counter;
	}*/
	
	for (int delta = 0; delta < 4; ++delta)
	{
		int newRow = deltaCoords[delta][0] + state.row;
		int newCol = deltaCoords[delta][1] + state.col;

		if (isSafe(newRow, newCol))
		{
			if (state.counter + matrix[newRow][newCol] < minCostPath)
			{
				costMatrix[newRow][newCol] = state.counter + matrix[newRow][newCol];
				TravelingSalesperson newState(newRow, newCol, state.counter + matrix[newRow][newCol]);
			}
		}
	}
}

void mainTravelingSalesperson(int row, int col)
{
	TravelingSalesperson firstState(row, col, 0);
	dfsTravelingSalesperson(firstState);
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

		int breaks = 0;

		mainTravelingSalesperson(0, 0);
		cout << "#" << test_cases << " " << minCostPath << '\n';
		minCostPath = INT_MAX;
		
	}

	return 0;
}
