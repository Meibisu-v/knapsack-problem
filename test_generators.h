#include "knapsack.h"
#include "random_library.h"

KnapsackTest getRandomTest(int maxN, int maxW, int maxP) {
	int n = getRandomInt(1, maxN);
	vector<Stone> stones;
	long long sumW = 0;
	for (int i = 0; i < n; ++i) {
		stones.push_back(Stone(getRandomInt(1, maxW), getRandomInt(1, maxP)));
		sumW += stones.back().weight;
	}
	return KnapsackTest(stones, getRandomLong(1, sumW));
}

KnapsackTest getWorstTest(int n, int scale) {
	vector<Stone> stones;
	if (n & 1)
		stones.push_back(Stone(1000000000, scale));
	for (int i = 0; i < n / 2; ++i) {
		stones.push_back(Stone(1, scale));
		stones.push_back(Stone(1, 2 * scale - 1));
	}

	long long sumW = 0;
	for (int i = 1; i < stones.size(); ++i)
		sumW += stones[i].weight;

	if (stones.size() != n)
		throw runtime_error("Incorrect test");

	return KnapsackTest(stones, n / 2);
}
