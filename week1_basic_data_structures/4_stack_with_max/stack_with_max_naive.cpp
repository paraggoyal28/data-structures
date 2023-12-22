#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using std::cin;
using std::cout;
using std::max_element;
using std::string;
using std::vector;

class StackWithMax
{
    vector<int> stack;
    vector<int> maxStack;

public:
    void Push(int value)
    {
        stack.push_back(value);
        if (maxStack.empty())
            maxStack.push_back(value);
        else
            maxStack.push_back(std::max(maxStack.back(), value));
    }

    void Pop()
    {
        assert(stack.size());
        stack.pop_back();
        maxStack.pop_back();
    }

    int Max() const
    {
        return maxStack.back();
    }
};

int main()
{
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i)
    {
        cin >> query;
        if (query == "push")
        {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop")
        {
            stack.Pop();
        }
        else if (query == "max")
        {
            cout << stack.Max() << "\n";
        }
        else
        {
            assert(0);
        }
    }
    return 0;
}