#include "test_generators.h"

bool processSmallCases() {
	for (int testNum = 0; testNum < 100; ++testNum) {
		KnapsackTest currentTest = getRandomTest(50, 100, 100);
		KnapsackSolution preciseSolution = solvePreciseKnapsack(currentTest.stones, currentTest.maxWeight);
		long long maximalRelevantProfit = getMaximalRelevantProfit(currentTest.stones, currentTest.maxWeight);
		long long preciseAnswer = preciseSolution.maximalReachableProfit;

		if (!checkSolution(currentTest.stones, currentTest.maxWeight, preciseSolution)) {
			cerr << "Something went wrong\n";
			return false;
		}

		for (int n = 1; n <= 10; ++n) {
			double eps = 1.0 / n;
			long long approximateAnswer = solveApproximateKnapsack(currentTest.stones, currentTest.maxWeight, eps).maximalReachableProfit;
			if (approximateAnswer < preciseAnswer - eps * maximalRelevantProfit) {
				cerr << "Approximation scheme is not working\n";
				cout << "Precise answer is " << preciseAnswer << "\n";
				cout << "Approximate answer is " << approximateAnswer << "\n";
				return false;
			}

			if (preciseAnswer > 0 && approximateAnswer != preciseAnswer) {
				cout << "Precision is " << (preciseAnswer - approximateAnswer) / 1.0 / maximalRelevantProfit << endl;
				cout << "Needed precision " << eps << endl << endl;
			}
		}
	}
	return true;
}

bool processLargeCases() {
	for (int testNum = 0; testNum < 10; ++testNum) {
		KnapsackTest currentTest = getRandomTest(20, 1000000000, 1000000000);
		for (int n = 1; n <= 50; ++n) {
			double eps = 1.0 / n;
			long long approximateAnswer = solveApproximateKnapsack(currentTest.stones, currentTest.maxWeight, eps).maximalReachableProfit;
			if (approximateAnswer < 0) {
				cerr << "Something went wrong\n";
				return false;
			}
		}
	}
	return true;
}

bool processWorstCases() {
	for (int testNum = 0; testNum < 50; ++testNum) {
		int n = getRandomInt(20, 100);
		int scale = getRandomInt(2, 1000);
		double eps = n / 1.0 / (2 * scale - 1) * scale;

		KnapsackTest currentTest = getWorstTest(n, scale);

		KnapsackSolution preciseSolution = solvePreciseKnapsack(currentTest.stones, currentTest.maxWeight);
		long long preciseAnswer = preciseSolution.maximalReachableProfit;
		long long maximalRelevantProfit = getMaximalRelevantProfit(currentTest.stones, currentTest.maxWeight);

		long long approximateAnswer = solveApproximateKnapsack(currentTest.stones, currentTest.maxWeight, eps).maximalReachableProfit;
		if (approximateAnswer < preciseAnswer - eps * maximalRelevantProfit) {
			cerr << "Approximation scheme is not working\n";
			cout << "Precise answer is " << preciseAnswer << "\n";
			cout << "Approximate answer is " << approximateAnswer << "\n";
			return false;
		}

		if (preciseAnswer > 0 && approximateAnswer != preciseAnswer) {
			cout << "Precision is " << (preciseAnswer - approximateAnswer) / 1.0 / maximalRelevantProfit << endl;
			cout << "Needed precision " << eps << endl << endl;
		}
	}

	return true;
}

int main() {

	cout.precision(15);
	cout << fixed;

	bool correct = true;
	
	correct &= processSmallCases();

	correct &= processLargeCases();

	correct &= processWorstCases();

	if (correct) {
		cout << "All tests were proceeded correctly\n";
	}

}