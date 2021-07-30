#include <string>
#include "Node.cpp"
using namespace std;
class RegExParser
{

public:
  string reg, ori;
  Node *root;
  RegExParser(string input)
  {
    root = nullptr;
    //reg = input;
    ori = input;
    reg = "";
    for (int i = 0; i < ori.length() - 1; i++)
    {
      reg.push_back(ori[i]);
      if (ori[i] == '+' || ori[i] == '?' || ori[i] == '*' || ori[i] == ')')
      {
        if (ori[i + 1] >= 'a' && ori[i + 1] <= 'z')
          reg.push_back(' ');
        if (ori[i + 1] == '(')
          reg.push_back(' ');
      }
      if (ori[i] >= 'a' && ori[i] <= 'z')
      {
        if (ori[i + 1] >= 'a' && ori[i + 1] <= 'z')
          reg.push_back(' ');
      }
    }
    reg.push_back(ori[ori.length() - 1]);
  }

  char peek()
  {
    return reg.at(0);
  }

  void eat(char c)
  {
    if (peek() == c)
      reg = reg.substr(1);
  }

  char next()
  {
    char c = peek();
    eat(c);
    return c;
  }

  bool more()
  {
    return reg.length() > 0;
  }

  void parsing()
  {

    root = new Node();
    root = regex();
    root->print2DUtil(root, 0);
  }

  int op_map(char c)
  {
    if (c == '(')
      return 4;
    else if (c == '|')
      return 3;
    else if (c == ' ')
      return 2;
    else if (c == '*' || c == '+' || c == '?')
      return 1;
    else
      return 0;
  }

  stack<string> postorder()
  {
    stack<string> nodes;
    stack<char> aux;
    for (char c : reg)
    {
      if (!aux.empty() && op_map(c) > op_map(aux.top()) && c != '(')
      {
        while (!aux.empty() && op_map(c) > op_map(aux.top()))
        {
          char a = aux.top();
          aux.pop();
          if (a == ')')
          {
            while (aux.top() != '(')
            {
              a = aux.top();
              aux.pop();
              if (a != ' ')
                nodes.push({a});
              else
                nodes.push("conc");
            }
            aux.pop();
          }
          else
          {
            if (a != ' ')
              nodes.push({a});
            else
              nodes.push("conc");
          }
        }
      }
      if (c >= 'a' && c <= 'z')
        nodes.push({c});
      else
        aux.push(c);
    }

    while (!aux.empty())
    {
      char a = aux.top();
      aux.pop();
      if (a == ')')
      {
        while (aux.top() != '(')
        {
          a = aux.top();
          aux.pop();
          if (a != ' ')
            nodes.push({a});
          else
            nodes.push("conc");
        }
        aux.pop();
      }
      else
      {
        if (a != ' ')
          nodes.push({a});
        else
          nodes.push("conc");
      }
    }

    stack<string> result;
    while (!nodes.empty())
    {
      auto cur = nodes.top();
      nodes.pop();
      result.push(cur);
    }

    return result;

    /*root = new Node();
    root = regex();
    root->postorder(root, nodes);
    return nodes;*/
  }

  Node *regex()
  {
    Node *n = new Node();
    n->left = term();
    if (more() && (peek() == '|' || peek() == ' '))
    {
      switch (peek())
      {
      case '|':
        eat('|');
        n->data = "|";
        break;
      case ' ':
        eat(' ');
        n->data = "conc";
        break;
      }
      n->right = regex();
    }
    else
    {
      n = n->left;
    }
    return n;
  }

  Node *term()
  {
    Node *n = new Node();

    while (more() && peek() != ')' && peek() != '|' && peek() != ' ')
    {
      n->left = factor();
      n = n->left;
    }
    return n;
  }

  Node *factor()
  {
    Node *n = new Node();
    auto p = peek();
    n->left = base();
    int flag = 0;
    while (more() && (peek() == '*' || peek() == '?' || peek() == '+'))
    {
      flag = 1;
      n->data = peek();
      switch (peek())
      {
      case '*':
        eat('*');
        break;
      case '+':
        eat('+');
        break;
      case '?':
        eat('?');
        break;
      }
    }
    if (flag == 0)
    {
      n = n->left;
      n->left = nullptr;
    }
    return n;
  }

  Node *base()
  {
    Node *n = new Node();
    switch (peek())
    {
    case '(':
      eat('(');
      n = regex();
      eat(')');
      break;
    default: //letra
      n->data = peek();
      next();
      break;
    }
    return n;
  }
};