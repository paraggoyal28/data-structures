#include <iostream>
#include <vector>

using namespace std;

vector<long long> precomputeHashes(const string &str, long long multiplier, long long prime)
{

	size_t len = str.length();
	vector<long long> hashes(len + 1, 0);
	for (size_t i = 1; i <= len; ++i)
	{
		hashes[i] = (multiplier * hashes[i - 1] + str[i - 1]) % prime;
	}
	return hashes;
}

long long modularExponentiation(long long base, long long power, long long prime)
{

	long long res = 1;
	while (power > 0)
	{
		if (power & 1)
		{
			res = (res * base) % prime;
		}
		base = (base * base) % prime;
		power /= 2;
	}
	return res;
}

vector<long long> precomputeYValues(long long multiplier, long long prime, long long length)
{
	vector<long long> y(length + 1, 0);
	for (long long len = 1; len <= length; ++len)
	{
		y[len] = modularExponentiation(multiplier, len, prime);
	}
	return y;
}

long long subStringHash(vector<long long> &hashValues, int start, int length, long long multiplier, long long prime, vector<long long> &yValues)
{

	return (hashValues[start + length] % prime - (yValues[length] % prime * hashValues[start] % prime) % prime + prime) % prime;
}

vector<int> solve(int k, const string &text, const string &pattern)
{
	vector<int> pos;

	long long multiplier = 1234;
	long long prime = 1000000009;

	int textLen = text.length();
	int patternLen = pattern.length();
	vector<long long> tHashes = precomputeHashes(text, multiplier, prime);
	vector<long long> pHashes = precomputeHashes(pattern, multiplier, prime);
	vector<long long> yValues = precomputeYValues(multiplier, prime, textLen);

	for (int i = 0; i < textLen - patternLen + 1; ++i)
	{
		int k_i = 0;
		int a = i;
		int base_b = i + patternLen - 1;
		int b = base_b;

		while (k_i <= k)
		{
			int mismatch = -1;

			while (a <= b)
			{
				int mid = a + (b - a) / 2;

				long long tHash = subStringHash(tHashes, a, mid - a + 1, multiplier, prime, yValues);
				long long pHash = subStringHash(pHashes, a - i, mid - a + 1, multiplier, prime, yValues);

				if (tHash == pHash)
				{
					a = mid + 1;
				}
				else
				{
					mismatch = mid;
					b = mid - 1;
				}
			}

			if (mismatch != -1)
			{
				k_i += 1;
				a = mismatch + 1;
				b = base_b;
			}
			else
			{
				pos.push_back(i);
				break;
			}
		}
	}
	return pos;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0);
	int k;
	string t, p;
	while (cin >> k >> t >> p)
	{
		auto a = solve(k, t, p);
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}
}
