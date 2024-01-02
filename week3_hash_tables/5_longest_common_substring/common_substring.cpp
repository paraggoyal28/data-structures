#include <iostream>
#include <unordered_map>
#include <vector>
#define ull unsigned long long int
using namespace std;

struct Answer
{
	size_t i, j, len;
};

Answer newAnswer(size_t i, size_t j, size_t len)
{
	Answer ans;
	ans.i = i;
	ans.j = j;
	ans.len = len;
	return ans;
}

size_t polyHash(const string &s, const size_t prime)
{
	static const size_t multiplier = 263;
	ull hash = 0;
	for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
		hash = ((hash % prime * multiplier % prime) % prime + s[i] % prime) % prime;
	return hash;
}

Answer findCommonSubstring(const string &s, const string &t, int length)
{
	unordered_map<long long, long long> shm1;
	unordered_map<long long, long long> shm2;
	int tLength = t.length();
	int sLength = s.length();
	vector<long long> tHashValues1(tLength - length + 1);
	vector<long long> tHashValues2(tLength - length + 1);
	vector<long long> sHashValues1(sLength - length + 1);
	vector<long long> sHashValues2(sLength - length + 1);
	static const size_t prime1 = 1000000007;
	static const size_t prime2 = 1000000009;
	static const size_t multiplier = 263;

	string endS = s.substr(sLength - length);
	string endT = t.substr(tLength - length);
	tHashValues1[tLength - length] = polyHash(endT, prime1);
	tHashValues2[tLength - length] = polyHash(endT, prime2);
	sHashValues1[sLength - length] = polyHash(endS, prime1);
	sHashValues2[sLength - length] = polyHash(endS, prime2);
	shm1[sHashValues1[sLength - length]] = sLength - length;
	shm2[sHashValues2[sLength - length]] = sLength - length;
	ull y1 = 1;
	ull y2 = 1;
	for (int itr = 0; itr < length; ++itr)
	{
		y1 = (y1 % prime1 * multiplier % prime1) % prime1;
		y2 = (y2 % prime2 * multiplier % prime2) % prime2;
	}

	for (int itr = sLength - length - 1; itr >= 0; --itr)
	{
		sHashValues1[itr] = ((multiplier % prime1 * 1LL * sHashValues1[itr + 1] % prime1) % prime1 + s[itr] % prime1 - (y1 % prime1 * 1LL * s[itr + length] % prime1) % prime1 + prime1) % prime1;
		sHashValues2[itr] = ((multiplier % prime2 * 1LL * sHashValues2[itr + 1] % prime2) % prime2 + s[itr] % prime2 - (y2 % prime2 * 1LL * s[itr + length] % prime2) % prime2 + prime2) % prime2;
		shm1[sHashValues1[itr]] = itr;
		shm2[sHashValues2[itr]] = itr;
	}
	if (shm1.find(tHashValues1[tLength - length]) != shm1.end() && shm2.find(tHashValues2[tLength - length]) != shm2.end() && shm1[tHashValues1[tLength - length]] == shm2[tHashValues2[tLength - length]])
	{
		return newAnswer(shm1[tHashValues1[tLength - length]], tLength - length, length);
	}
	for (int itr = tLength - length - 1; itr >= 0; --itr)
	{
		tHashValues1[itr] = ((multiplier % prime1 * 1LL * tHashValues1[itr + 1] % prime1) % prime1 + t[itr] % prime1 - (y1 % prime1 * 1LL * t[itr + length] % prime1) % prime1 + prime1) % prime1;
		tHashValues2[itr] = ((multiplier % prime2 * 1LL * tHashValues2[itr + 1] % prime2) % prime2 + t[itr] % prime2 - (y2 % prime2 * 1LL * t[itr + length] % prime2) % prime2 + prime2) % prime2;
		if (shm1.find(tHashValues1[itr]) != shm1.end() && shm2.find(tHashValues2[itr]) != shm2.end() && shm1[tHashValues1[itr]] == shm2[tHashValues2[itr]])
		{
			return newAnswer(shm1[tHashValues1[itr]], itr, length);
		}
	}
	return newAnswer(-1, -1, -1);
}

Answer solve(const string &s, const string &t)
{
	Answer ans = {0, 0, 0};
	int sLength = s.length();
	int tLength = t.length();
	int maxCommonLength = min(sLength, tLength);
	int minCommonLength = 0;

	while (minCommonLength <= maxCommonLength)
	{

		int midCommonLength = minCommonLength + (maxCommonLength - minCommonLength) / 2;
		Answer common = findCommonSubstring(s, t, midCommonLength);
		if (common.len == midCommonLength)
		{
			ans = common;
			minCommonLength = midCommonLength + 1;
		}
		else
		{
			maxCommonLength = midCommonLength - 1;
		}
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t)
	{
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
