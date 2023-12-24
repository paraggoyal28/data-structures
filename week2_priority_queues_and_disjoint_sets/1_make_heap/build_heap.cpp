#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::swap;
using std::vector;

class HeapBuilder
{
private:
  vector<int> data_;
  vector<pair<int, int>> swaps_;

  void WriteResponse() const
  {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i)
    {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData()
  {
    int n;
    cin >> n;
    data_.resize(n);
    for (int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void siftDown(int index, int n)
  {
    int minimum = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < n && data_[left] < data_[minimum])
    {
      minimum = left;
    }
    if (right < n && data_[right] < data_[minimum])
    {
      minimum = right;
    }

    if (minimum != index)
    {
      swaps_.push_back({index, minimum});
      swap(data_[index], data_[minimum]);
      siftDown(minimum, n);
    }
  }

  void GenerateSwaps()
  {
    swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap,
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    size_t size = data_.size();
    for (int i = size / 2; i >= 0; --i)
    {
      siftDown(i, size);
    }
  }

public:
  void Solve()
  {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
