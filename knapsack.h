#include "stone.h"
#include <iostream>

using namespace std;

struct KnapsackSolution {
	long long maximalReachableProfit;
	vector<int> takenStones;
	KnapsackSolution() {}
	KnapsackSolution(long long maximalReachableProfit, vector<int> takenStones) :maximalReachableProfit(maximalReachableProfit), takenStones(takenStones) {}
};

struct KnapsackTest {
	vector<Stone> stones;
	long long maxWeight;
	KnapsackTest(vector<Stone> stones, long long maxWeight) :stones(stones), maxWeight(maxWeight) {}
};

KnapsackSolution solvePreciseKnapsack(vector<Stone>& stones, long long maxWeight) {
	int maxProfit = getMaximalProfit(stones) * stones.size();
	vector<vector<long long>> dp(stones.size() + 1, vector<long long>(maxProfit + 1, -1));
	vector<vector<int>> lastTakenStone(stones.size() + 1, vector<int>(maxProfit + 1, -1));
	dp[0][0] = 0;
	for (int num = 0; num < stones.size(); ++num) {
		Stone item = stones[num];
		dp[num + 1] = dp[num];
		lastTakenStone[num + 1] = lastTakenStone[num];
		for (int currentProfit = maxProfit; currentProfit >= item.profit; --currentProfit) {
			if (dp[num][currentProfit - item.profit] != -1 && (dp[num + 1][currentProfit] == -1 || dp[num + 1][currentProfit] > dp[num][currentProfit - item.profit] + item.weight)) {
				dp[num + 1][currentProfit] = dp[num][currentProfit - item.profit] + item.weight;
				lastTakenStone[num + 1][currentProfit] = num;
			}
		}
	}
	
	for (int currentProfit = maxProfit; currentProfit >= 0; --currentProfit) {
		if (dp[stones.size()][currentProfit] != -1 && dp[stones.size()][currentProfit] <= maxWeight) {
			KnapsackSolution result;
			result.maximalReachableProfit = currentProfit;
			int lastStoneId = lastTakenStone[stones.size()][currentProfit];
			while (lastStoneId >= 0) {
				result.takenStones.push_back(lastStoneId);
				currentProfit -= stones[lastStoneId].profit;
				lastStoneId = lastTakenStone[lastStoneId][currentProfit];
			}
			return result;
		}
	}
}

KnapsackSolution solveApproximateKnapsack(vector<Stone> stones, long long maxWeight, double eps) {
	//eraseBigWeights(stones, maxWeight);
	if (stones.empty())
		return KnapsackSolution(0, vector<int>());
	int maxProfit = getMaximalProfit(stones);
	int scale = max((int)(eps * maxProfit / stones.size()), 1);

	vector<Stone> scaledStones;
	for (Stone item : stones) {
		scaledStones.push_back(Stone(item.weight, item.profit / scale));
	}

	KnapsackSolution result;
	result.maximalReachableProfit = 0;
	result.takenStones = solvePreciseKnapsack(scaledStones, maxWeight).takenStones;
	for (int id : result.takenStones)
		result.maximalReachableProfit += stones[id].profit;
	return result;
}

bool checkSolution(vector<Stone> stones, long long maximalWeight, KnapsackSolution& solution) {
	long long actualWeight = 0;
	long long actualProfit = 0;
	for (int id : solution.takenStones) {
		actualWeight += stones[id].weight;
		actualProfit += stones[id].profit;
	}

	if (actualWeight <= maximalWeight && actualProfit == solution.maximalReachableProfit)
		return true;

	if (actualWeight > maximalWeight)
		throw new runtime_error("Too heavy solution");

	if (actualProfit != solution.maximalReachableProfit)
		throw new runtime_error("Actual profit is not equal to the outputted");

	return false;
}