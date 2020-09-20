#include "EratosthensSieve.h"
 
vector<ulli> EratosthensSieve::sieve(ulli n)
{
	vector<bool> prime(n + 1, true);

	prime[0] = false;
	prime[1] = false;
	int m = sqrt(n);

	for (ulli p = 2; p <= m; p++)
	{
		if (prime[p])
		{
			for (ulli i = p * 2; i <= n; i += p)
				prime[i] = false;
		}
	}
	vector<ulli> ans;
	for (int i = 0; i < n; i++)
		if (prime[i])
			ans.push_back(i);
	return ans;

}
vector<int> EratosthensSieve::SieveOfEratosthenes(int n)
{
	vector<int> res;
	vector<bool> prime(n + 1, true);
	//memset(prime, true, sizeof(prime));

	for (int p = 2; p * p <= n; p++)
	{
		if (prime[p] == true)
		{
			for (int i = p * p; i <= n; i += p)
				prime[i] = false;
		}
	}

	for (int p = 2; p <= n; p++)
		if (prime[p]) {
			res.push_back(p);
		}
	return res;
}
bool EratosthensSieve::isZero(ulli i)
{
	return i == 0;
}

vector<ulli> EratosthensSieve::sieveRange(ulli start, ulli end)
{

	// find primes from [0..start] range 
	vector<ulli> s1 = sieve(start);

	// find primes from [0..end] range  
	vector<ulli> s2 = sieve(end);

	vector<ulli> ans(end - start);

	// find set difference of two vectors and 
	// push result in vector ans 
	// O(2*(m+n)-1)  
	set_difference(s2.begin(), s2.end(), s1.begin(),
		s2.end(), ans.begin());

	// remove extra zeros if any. O(n) 
	vector<ulli>::iterator itr =
		std::remove_if(ans.begin(), ans.end(), [](ulli& i) { return i == 0; });

	// resize it. // O(n) 
	ans.resize(itr - ans.begin());

	return ans;

}
