#include <iostream>
#include <vector>

using namespace std;

class Solver
{
	string s;

public:
	static const size_t multiplier = 263;
	static const size_t prime1 = 1000000007;
	static const size_t prime2 = 1000000009;
	vector<long long> h1;
	vector<long long> h2;
	long long power(int l, const size_t prime)
	{
		long long res = 1;
		long long m = multiplier;
		while (l > 0)
		{
			if (l % 2)
			{
				res = (res * m) % prime;
			}
			m = (m * m) % prime;
			l /= 2;
		}
		return res;
	}

	Solver(string s) : s(s)
	{
		// initialization, precalculation
		int n = s.length();
		h1.resize(n + 1, 0);
		h2.resize(n + 1, 0);

		for (int i = 1; i <= n; ++i)
		{
			h1[i] = ((h1[i - 1] % prime1 * multiplier % prime1) % prime1 + s[i - 1]) % prime1;
			h2[i] = ((h2[i - 1] % prime2 * multiplier % prime2) % prime2 + s[i - 1]) % prime2;
		}
	}
	bool ask(int a, int b, int l)
	{
		long long multiplier_power_l1 = power(l, prime1);
		long long multiplier_power_l2 = power(l, prime2);

		long long hash1_prime1 = (h1[a + l] % prime1 - (multiplier_power_l1 % prime1 * h1[a] % prime1) % prime1 + prime1) % prime1;
		long long hash2_prime1 = (h1[b + l] % prime1 - (multiplier_power_l1 % prime1 * h1[b] % prime1) % prime1 + prime1) % prime1;

		long long hash1_prime2 = (h2[a + l] % prime2 - (multiplier_power_l2 % prime2 * h2[a] % prime2) % prime2 + prime2) % prime2;
		long long hash2_prime2 = (h2[b + l] % prime2 - (multiplier_power_l2 % prime2 * h2[b] % prime2) % prime2 + prime2) % prime2;

		return hash1_prime1 == hash2_prime1 && hash1_prime2 == hash2_prime2;
	}
};

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++)
	{
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
