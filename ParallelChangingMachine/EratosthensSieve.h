#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>

using namespace std;
typedef unsigned long long int ulli;

class EratosthensSieve
{
public:
	EratosthensSieve() {

	}
	

	vector<ulli> sieve(ulli n);
	bool isZero(ulli i);
	vector<int> SieveOfEratosthenes(int n);
	vector<ulli> sieveRange(ulli start, ulli end);
	
};

