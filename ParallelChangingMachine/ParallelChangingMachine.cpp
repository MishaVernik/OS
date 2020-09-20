/*
	@author		MV
	@datetime	9/20/2020
*/
#include <iostream>
#include <map>
#include <stdio.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include <set>
#include <thread>
#include <atomic>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "EratosthensSieve.h"
#include "InputData.h"
#include "ParallelChangingMachine.h"

using namespace std::chrono;
using namespace std;

EratosthensSieve sieve;

int COIN;
vector<int> PRIME_NUMBERS;

// could be used.
// atomic_bool f1{false}, f2{false}
bool thread1WantsToEnter = false;
bool thread2WantsToEnter = false;
int TURN = 1;
map<int, vector<pair<int, bool>>> COINS;

void ProcessA() {
	thread1WantsToEnter = true;
	for (; ;) {
		while (thread2WantsToEnter) {
			if (TURN == 2) {
				thread1WantsToEnter = false;
				while (TURN != 1) {

				}
				thread1WantsToEnter = true;
			}
		}
		//printf("Entry Thread 1 in critical section\n");
		ShowResult();
		this_thread::sleep_for(chrono::milliseconds(20));
		//printf("Exit Thread 1 in critical section\n");

		TURN = 2;
		thread1WantsToEnter = false;
	}

}

void ProcessB() {
	thread2WantsToEnter = true;
	for (; ;) {
		while (thread1WantsToEnter) {
			if (TURN == 1) {
				thread2WantsToEnter = false;

				while (TURN != 2) {

				}
				thread2WantsToEnter = true;
			}
		}
		//printf("Entry Thread 2 in critical section\n");
		GetCoin();
		this_thread::sleep_for(chrono::milliseconds(20));
		//printf("Exit Thread 2 in critical section\n");
		TURN = 1;
		thread2WantsToEnter = false;
	}

}

int GetHash(vector<int> v) {

	if (v.size() == 0) return -1;
	sort(v.begin(), v.end());
	/*ulli start = 1;
	auto mx = INT_MIN;
	for (auto el : v) {
		mx = max(mx, el);
	}
	ulli end = mx;
	*/

	int hash = 0;
	for (int i = 0; i < v.size(); i++) {
		hash = (hash + v[i] * (int)PRIME_NUMBERS[i]) % 1000000007;
	}

	return hash;
}

void GetAllExchanges(vector<vector<int>>& result,
	vector<int> coinsArray,
	vector<int> quantityCoins,
	vector<int> tempCoins,
	int coinSum,
	set<int>& st) {

	int hash = GetHash(tempCoins);
	if (coinSum == 0 && st.find(hash) == st.end() && tempCoins.size() > 1) {
		st.insert(hash);
		result.push_back(tempCoins);
		return;
	}
	if (coinSum < 0) return;
	for (int i = 0; i < coinsArray.size(); i++) {
		if (quantityCoins[i] == 0) continue;
		quantityCoins[i]--;
		tempCoins.push_back(coinsArray[i]);
		GetAllExchanges(result, coinsArray, quantityCoins, tempCoins, coinSum - coinsArray[i], st);
		tempCoins.pop_back();
	}

}

void ShowResult()
{
	int coinValue = COIN;
	vector<int> coinsArray;
	vector<int> quantityCoins;
	vector<int> p;
	vector<vector<int>> allCoinExhangesWays;
	set<int> st;
	bool isValid = true;
	for (auto& c : COINS) {
		coinsArray.push_back(c.first);
		int quantity = 0;
		for (int i = 0; i < c.second.size(); i++) {
			if (c.second[i].second == true) {
				quantity++;
			}
		}
		if (quantity > 0)
			quantityCoins.push_back(quantity);
		else
			coinsArray.pop_back();
	}

	GetAllExchanges(allCoinExhangesWays, coinsArray, quantityCoins, p, coinValue, st);

	int minSize = INT_MAX;
	int minIndex = 0;
	for (int i = 0; i < allCoinExhangesWays.size(); i++) {
		if (minSize > allCoinExhangesWays[i].size()) {
			minSize = allCoinExhangesWays[i].size();
			minIndex = i;
		}
	}
	if (allCoinExhangesWays.size() > 0 && COIN > 0) {

		cout << "\nYour coin has been changed: " << endl;
		for (int i = 0; i < allCoinExhangesWays[minIndex].size(); i++) {
			cout << allCoinExhangesWays[minIndex][i] << " ";
			for (int index = 0; index < COINS[allCoinExhangesWays[minIndex][i]].size(); index++) {
				if (COINS[allCoinExhangesWays[minIndex][i]][index].second == true) {
					COINS[allCoinExhangesWays[minIndex][i]].erase(COINS[allCoinExhangesWays[minIndex][i]].begin() + index);
					break;
				}
			}
		}
		for (auto& c : COINS) {
			for (int i = 0; i < c.second.size(); i++) {
				c.second[i].second = true;
			}
		}
		COIN = 0;
		cout << endl;
	}
	else if (COIN != 0) {
		cout << "The value " <<  COIN << " cannot be changed." << endl;
		COIN = 0;
	}

#ifdef DEBUG
	// DP sovled problem, but here it's totally unused.

	vector<int> vCoins;
	for (auto el : coins)
		vCoins.push_back(el.first);

	vector<pair<int, vector<int>>> dp(coin + 1);
	for (auto el : dp) {
		el = { coin + 1, {} };
	}
	dp[0].first = 0;

	/*vector<vector<int>> table(coin + 1, vector<int>(coins.size(), coin + 1));
	table[0][0] = 0;*/

	for (int i = 1; i <= coin; i++) {
		for (int j = 0; j < vCoins.size(); j++) {
			if (vCoins[j] <= i) {
				if (dp[i].first == dp[i - vCoins[j]].first + 1) {
					//dp[i - vCoins[j]].second.push_back()
				}
				else if (dp[i].first > dp[i - vCoins[j]].first + 1) {
					dp[i].second.clear();
					dp[i].first = dp[i - vCoins[j]].first + 1;
				}
			}
		}
	}


	auto cp = coins;
	int saveCoin = coin;
	vector<int> result;
	for (auto iter = coins.rbegin(); iter != coins.rend(); ++iter) {
		if (coin == 0) break;
		while (iter->second > 0 && coin - iter->first >= 0) {
			result.push_back(iter->first);
			iter->second--;
			coin -= iter->first;
		}
	}

#endif // DEBUG
		}


void GetCoin()
{
	for (auto& c : COINS) {
		for (int i = 0; i < c.second.size(); i++) {
			c.second[i].second = true;
		}
	}
	cout << "\nPlease enter the coin: ";
	cin >> COIN;
	if (COIN > 0)
		COINS[COIN].push_back({ 1, false });
	else {
		COIN = 0;
		cout << "Please type only number bigger than 0." << endl;
	}
}


int main()
{
	ifstream file("input.txt");
	InputData inputData;

	PRIME_NUMBERS = sieve.SieveOfEratosthenes(10000);
	auto data = inputData.ReadFromFile(file);
	for (auto el : data) {
		if (COINS.find(el.first) == COINS.end()) {
			vector<pair<int, bool>> vp;
			COINS[el.first] = vp;
		}

		for (int i = 0; i < el.second; i++) {
			COINS[el.first].push_back({ 1, true });
		}
	}

	thread processB(ProcessB);
	thread processA(ProcessA);

	processA.join();
	processB.join();
	return 0;
}
