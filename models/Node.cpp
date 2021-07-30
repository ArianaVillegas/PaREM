#ifndef NODE_H
#define NODE_H


#include <string>
#include <stack>
#include <iostream>
using namespace std;

#define COUNT 10

class Node
{
public:
  Node *left;
  Node *right;
  Node *parent;
  std::string data = "0";

  Node()
  {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
  ~Node() {}

  void print2DUtil(Node *root, int space)
  {
    // Base case
    if (root == NULL)
      return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
      cout << " ";
    cout << root->data << "\n";

    // Process left child
    print2DUtil(root->left, space);
  }

  void postorder(Node *root, stack<string> &nodes)
  {
    if (root == NULL)
      return;
    nodes.push(root->data);
    postorder(root->left, nodes);
    postorder(root->right, nodes);
  }
};

#endif