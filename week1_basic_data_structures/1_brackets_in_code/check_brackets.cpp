#include <iostream>
#include <stack>
#include <string>

using std::endl;

struct Bracket
{
    Bracket(char type, int position) : type(type),
                                       position(position)
    {
    }

    bool Matchc(char c)
    {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main()
{
    std::string text;
    getline(std::cin, text);

    std::stack<Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position)
    {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{')
        {
            // Process opening bracket, write your code here
            opening_brackets_stack.push(Bracket(next, position + 1));
        }

        if (next == ')' || next == ']' || next == '}')
        {
            // Process closing bracket, write your code here
            if (opening_brackets_stack.empty())
            {
                std::cout << position + 1 << endl;
                return 0;
            }
            Bracket prev = opening_brackets_stack.top();
            opening_brackets_stack.pop();
            if (!prev.Matchc(next))
            {
                std::cout << position + 1 << endl;
                return 0;
            }
        }
    }

    // Printing answer, write your code here
    if (opening_brackets_stack.empty())
    {
        std::cout << "Success" << endl;
        return 0;
    }

    while (opening_brackets_stack.size() > 1)
        opening_brackets_stack.pop();

    std::cout << opening_brackets_stack.top().position << endl;

    return 0;
}
