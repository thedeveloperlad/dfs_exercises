#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;
/*
	The Samsung Tire Problem

	The maximum air pressure of the samsung tire is K.

	The tire gets damaged if the inner air pressure of the tire exceeds K or is less than 0.


*/
#define N_MAX 8

struct SamsungTireProblem
{
	int inflate[N_MAX];
	int deflate[N_MAX];
};

int K = 0; 
int N = 0;
SamsungTireProblem tires;

bool stopPermutation = false;
int totalPressure = -1;

bool findInitialPressure(int inflate[N_MAX], int deflate[N_MAX], int initialPressure)
{
	int tempDeflateResult = 0;

	for (int row = 0; row < N; ++row)
	{
		int tempInflateResult = inflate[row] + initialPressure + tempDeflateResult;

		if (tempInflateResult > K || tempInflateResult < 0 || tempDeflateResult < 0)
		{
			return false;
		}
		tempDeflateResult = tempInflateResult - deflate[row];

		if (tempDeflateResult < 0)
		{
			return false;
		}
		initialPressure = 0;
	}
	return true;
} 

void dfsPermutationSamsungTire(int inflate[N_MAX], int deflate[N_MAX], int index, int end, int initialPressure)
{
	if (index == end)
	{
		if (findInitialPressure(inflate, deflate, initialPressure))
		{
			stopPermutation = true;
		}
		return;
	}
	else
	{
		if (stopPermutation == false)
		{
			for (int i = index; i <= end; i++)
			{
				swap(inflate[index], inflate[i]);
				swap(deflate[index], deflate[i]);
				dfsPermutationSamsungTire(inflate, deflate, index + 1, end, initialPressure); //dfs
				swap(inflate[index], inflate[i]);
				swap(deflate[index], deflate[i]);
			}
		}
	}
}

bool mainTyreProblem(int initialPressure)
{
	dfsPermutationSamsungTire(tires.inflate, tires.deflate, 0, N - 1, initialPressure);
	return stopPermutation;
}

int main()
{
	int T = 0;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int test_cases = 0; test_cases <= T; ++test_cases)
	{
		cin >> N;
		cin >> K;

		//inflate
		for (int row = 0; row < N; ++row)
		{
			cin >> tires.inflate[row];
		}
		//defalte
		for (int row = 0; row < N; ++row)
		{
			cin >> tires.deflate[row];
		}

		// loop of initial pressure (IP)
		for (int initialPresure = 0; initialPresure < K; ++initialPresure)
		{
			//do something
			if (mainTyreProblem(initialPresure))
			{
				totalPressure = initialPresure;
				break;
			}
		}

		cout << "#" << test_cases << " " << totalPressure << '\n';
		stopPermutation = false;
		totalPressure = -1;
	}

	return 0;
}
