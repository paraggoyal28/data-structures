#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node
{
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool isBST(const vector<Node> &tree, int root, int left, int right)
{
  if (root == -1)
  {
    return true;
  }

  if ((left != -1 && tree[root].key < tree[left].key) || (right != -1 && tree[root].key > tree[right].key))
  {
    return false;
  }

  return isBST(tree, tree[root].left, left, root) && isBST(tree, tree[root].right, root, right);
}

bool IsBinarySearchTree(const vector<Node> &tree)
{
  // Implement correct algorithm here
  if (tree.empty())
    return true;
  return isBST(tree, 0, -1, -1);
}

int main()
{
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i)
  {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree))
  {
    cout << "CORRECT" << endl;
  }
  else
  {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
