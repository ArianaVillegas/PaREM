
/*

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include "Node.cpp"
using namespace std;
#define COUNT 10
char token;

void exp(Node* current);
void factor(Node* current);
void term(Node* current); 
void letra(Node* current);

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
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->data<<"\n";
 
    // Process left child
    print2DUtil(root->left, space);
}

void error(void){
  fprintf(stderr,"Error1 \n");
  exit(1);
}

void match(char expectedToken){
  if(token == expectedToken) token = getchar();
  else error();
}
 
int main(void) {
  int result;
  token = getchar();
  Node* root = new Node();
  exp(root);
  if(token == '\n'){
    printf("Result = %d\n",result);
    print2DUtil(root, 0);
  }
  else 
    error();
  return 0;
}

void exp(Node* current){
  
  current->left = new Node();
  factor(current->left);
  
  if (token =='|' ){
    match('|');
    current->right = new Node();  
    current->data ='|';
    exp(current->right);    
  }

}

void factor(Node*current){
  current->left =  new Node();
  if(token == '('){
    match('(');
    exp(current->left);
    match(')');
  }
  
  if(int(token)>63 && int(token)<98){
    letra(current->left);
  }
  current->data = "CONC";
  current->right =new Node();
  exp(current->right);
}

void letra(Node* current){
  current->data=token;
  token = getchar();
}

void symb(){

}
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include "Regx.cpp"

using namespace std;
int main(){
  auto reg = RegExParser("b?c|a*cf");
  reg.parsing();
}