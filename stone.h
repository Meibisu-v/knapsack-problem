#include <vector>
#include <algorithm>

const int MAXIMALPOSSIBLEWEIGHT = 1000000000;
const int MAXIMALPOSSIBLEPROFIT = 1000000000;

struct Stone {
	int weight;
	int profit;
	Stone(int weight, int profit) :weight(weight), profit(profit) {}
};

int getMaximalProfit(std::vector<Stone>& stones) {
	int res = 0;
	for (Stone item : stones)
		res = std::max(res, item.profit);
	return res;
}

int getMaximalWeight(std::vector<Stone>& stones) {
	int res = 0;
	for (Stone item : stones)
		res = std::max(res, item.weight);
	return res;
}

int getMaximalRelevantProfit(std::vector<Stone>& stones, long long maxWeight) {
	int res = 0;
	for (Stone item : stones)
		if (item.weight <= maxWeight)
			res = std::max(res, item.profit);
	return res;
}

void eraseBigWeights(std::vector<Stone>& stones, long long maxWeight) {
	std::vector<Stone> newStones;
	for (Stone item : stones)
		if (item.weight <= maxWeight)
			newStones.push_back(item);
	stones.swap(newStones);
}