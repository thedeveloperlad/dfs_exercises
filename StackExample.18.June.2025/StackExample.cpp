#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;
/*
	A queue is a linear data structure that follows the First-In, First-Out (FIFO) principle.
	This means the element inserted first will be the first one to be removed.
	In C++, you can use the std::queue container from the Standard Template Library (STL) to implement a queue.

*/

/*
	00 01 02 {-1,0},{0,1},{1,0},{0,-1}
	10 11 12
	20 21 22

	00 01 02 {-1,-1}, {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}
	10 11 12
	20 21 22
*/
#define MAX 5

struct Queue
{
	int* queue;
	int col;
	int cnt;

	/*Queue(int size) :
		row(r),
		col(c),
		cnt(cn) {
	}*/
};

void push(int value)
{

}

int pop()
{
	int value;

	return value;
}

int front()
{
	int value;

	return value;
}

bool empty()
{
	return true;
}

int main()
{
	int T = 0;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int test_cases = 0; test_cases < T; ++test_cases)
	{


		//mainShortestPathBinaryMatrix(0, 0);
		//cout << "#" << test_cases << " " << minimumPath << '\n';
		//minimumPath = INT_MAX;

	}

	return 0;
}