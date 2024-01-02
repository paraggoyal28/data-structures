#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::cin;
using std::string;
using std::unordered_map;
using std::vector;

struct Query
{
    string type, name;
    int number;
};

vector<Query> read_queries()
{
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string> &result)
{
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query> &queries)
{
    vector<string> result;
    unordered_map<int, string> number_to_name;

    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add")
        {
            number_to_name[queries[i].number] = queries[i].name;
        }
        else if (queries[i].type == "del")
        {
            number_to_name.erase(queries[i].number);
        }
        else
        {
            string response = "not found";
            if (number_to_name.find(queries[i].number) != number_to_name.end())
            {
                response = number_to_name[queries[i].number];
            }
            result.push_back(response);
        }
    return result;
}

int main()
{
    write_responses(process_queries(read_queries()));
    return 0;
}
