#include <iostream>
#include <vector>
#include <deque>

using std::cin;
using std::cout;
using std::deque;
using std::max;
using std::vector;

void max_sliding_window_naive(vector<int> const &A, int w)
{
    deque<int> maxElements;
    int n = A.size();
    for (int i = 0; i < w; ++i)
    {
        while (!maxElements.empty() && A[maxElements.back()] < A[i])
        {
            maxElements.pop_back();
        }

        maxElements.push_back(i);
    }
    for (int i = w; i < n; ++i)
    {
        cout << A[maxElements.front()] << " ";

        while (!maxElements.empty() && maxElements.front() <= i - w)
        {
            maxElements.pop_front();
        }

        while (!maxElements.empty() && A[maxElements.back()] < A[i])
        {
            maxElements.pop_back();
        }

        maxElements.push_back(i);
    }

    cout << A[maxElements.front()] << "\n";
    return;
}

int main()
{
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
