#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
typedef unsigned long long ull;

struct Data
{
    string pattern, text;
};

Data read_input()
{
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

size_t polyHash(const string &s)
{
    static const size_t multiplier = 263;
    static const size_t prime = 1000000007;
    ull hash = 0;
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
        hash = (hash * multiplier + s[i]) % prime;
    return hash;
}

vector<long long> precompute_hashes(const string &t, int patternLength)
{
    static const size_t multiplier = 263;
    static const size_t prime = 1000000007;
    ull hash = 0;
    int textLength = t.length();
    vector<long long> h(textLength - patternLength + 1);
    string endStr = t.substr(textLength - patternLength);
    h[textLength - patternLength] = polyHash(endStr);
    ull y = 1;
    for (int itr = 0; itr < patternLength; ++itr)
    {
        y = (y * multiplier) % prime;
    }
    for (int itr = textLength - patternLength - 1; itr >= 0; --itr)
    {
        h[itr] = ((multiplier % prime * 1LL * h[itr + 1] % prime) % prime + t[itr] % prime - (y % prime * 1LL * t[itr + patternLength] % prime) % prime + prime) % prime;
    }
    return h;
    // runtime O(T + P)
}

void print_occurrences(const std::vector<int> &output)
{
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

bool isEqual(const string &pattern, const string &textSubstring)
{
    int n = pattern.length();
    for (int itr = 0; itr < n; ++itr)
    {
        if (pattern[itr] != textSubstring[itr])
        {
            return false;
        }
    }
    return true;
}

std::vector<int> get_occurrences(const Data &input)
{
    const string &s = input.pattern, t = input.text;
    std::vector<int> ans;
    int textSize = t.length();
    int patternSize = s.length();
    int pHash = polyHash(s);
    vector<long long> h = precompute_hashes(t, patternSize);

    for (int itr = 0; itr <= textSize - patternSize; ++itr)
    {
        if (pHash != h[itr])
        {
            continue;
        }
        if (isEqual(t.substr(itr, patternSize), s))
        {
            ans.push_back(itr);
        }
    }

    return ans;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
