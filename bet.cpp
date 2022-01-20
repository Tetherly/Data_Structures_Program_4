// Created by Tyler Starling on 6/27/2021.
// COP 4530
// BET class source file

#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include "bet.h"
using namespace std;

/****Public Member Functions****/
BET::BET() {    //  default constructor
    root = new BinaryNode;  //  creates the root of the tree
}

BET::BET(const string &postfix) {   //  constructor that builds a tree based on the postfix expression
    root = new BinaryNode;  //  creates the root of the tree
    buildFromPostfix(postfix);  //  calls the buildFromPostfix function to handle the building of the tree
}

BET::BET(const BET & b) { //  copy constructor
    root = clone(b.root);   //  makes a deep copy using the clone function
}

BET::~BET() {   //  uses the private makeEmpty function to delete all nodes
    makeEmpty(root);    //  calls makeEmpty function for node deletion
}

bool BET::buildFromPostfix(const string &postfix) {

    stringstream tokenizer(postfix);   //  creates a StringStream for tokenization
    string token;   //  string used for parsing data
    stack<BinaryNode*> stacker; //  creates a stack for construction of the BET

    if(!empty()){   //  deletes existing nodes if tree contains nodes prior to function call
        makeEmpty(root);
    }

    while(!tokenizer.eof()){    //  parsing the input
        tokenizer >> token;

        if(token == "+" || token == "-" || token == "/" || token == "*"){   //  token is operator

            auto *newNode = new BinaryNode(token);    //  builds a new node for the operator

            newNode->left = stacker.top();  //  adds an operand to the left child of the operator node
            stacker.pop();  //  pops off the operand
            newNode->right = stacker.top(); //  adds an operand to the right child of the operator node
            stacker.pop();  //  pops off the operand
            stacker.push(newNode);  //  adds the operator to the stack

        }else{  //  check if token is operand
            for(char i : token){ //  check all characters in token
                if(isalnum(i == false)){ //  token is not an operand
                    cout << "\nError occurred trying to convert postfix expression. "
                            "The postfix expression was not valid.\n";
                    return false;
                }
            }
            //  token is operand
            auto *newNode = new BinaryNode(token);    //  builds a new node for the operand
            stacker.push(newNode);  //  pushes the operand onto the stack
        }
    }

    //  S.top is the final binary expression tree
    root = stacker.top();

    return true;    //  returns true if the tree is built successfully
}

const BET &BET::operator=(const BET & b) {    //  assignment operator =
    root = clone(b.root);   //  makes a deep copy using the clone function
    return *this;
}

void BET::printInfixExpression() {  //  prints out the infix expression; uses private recursive function
    printInfixExpression(root); //  recursive call
    cout << "\n";
}

void BET::printPostfixExpression() {    //  prints out the postfix expression; uses private recursive function
    printPostfixExpression(root);   //  recursive call
    cout << "\n";
}

size_t BET::size() {    //  returns the number of nodes in the tree; uses private recursive function
    return size(root);  //  recursive call
}

size_t BET::leaf_nodes() {  //  returns the number of leaf nodes in the tree; uses private recursive function
    return leaf_nodes(root);    //  recursive call
}

bool BET::empty() { //  returns true on an empty tree; false otherwise
    if(root != nullptr){    //  if the root node isn't the nullptr, then the tree is not empty
        return false;
    }
    return true;
}

/****Private Member Functions****/
void BET::printInfixExpression(BET::BinaryNode *n) {    //  outputs the corresponding infix expression
    int counterParenthesis = 0;
    if(n != nullptr){   //  checks if n is valid, so we can print
        if((n->left == nullptr) && (n->right == nullptr)){  //  no children option
            cout << n->element << " ";  //  just prints the node element
        }else{
            /*** PRINT RIGHT CHILD ***/
            if((n->element == "+") && (n->element == "-") && (n->element == "*") && (n->element == "/")){   //  operator
                if((n->right->element == "*") || (n->right->element == "/") || (n->right->element == "+") || (n->right->element == "-")){
                    if((n->element == "*") || (n->element == "/")){ //  higher precedence
                        cout << "( ";
                        counterParenthesis = 1;
                    }
                }
            }
            printInfixExpression(n->right); //  print out the right child

            if(counterParenthesis == 1){    //  closes parenthesis if needed
                cout << ") ";
            }
            counterParenthesis = 0; //  resets our counter to 0

            /*** PRINT PARENT NODE ***/
            cout << n->element << " ";  //  prints the parent

            /*** PRINT LEFT CHILD ***/
            if((n->element == "+") && (n->element == "-") && (n->element == "*") && (n->element == "/")){   //  operator
                if((n->left->element == "*") || (n->left->element == "/") || (n->left->element == "+") || (n->left->element == "-")){
                    if((n->element == "*") || (n->element == "/")){ //  higher precedence
                        cout << "( ";
                        counterParenthesis = 1;
                    }
                }
            }
            printInfixExpression(n->left); //  print out the left child

            if(counterParenthesis == 1){    //  closes parenthesis if needed
                cout << ") ";
            }
            counterParenthesis = 0; //  resets our counter to 0
        }
    }
}

void BET::makeEmpty(BET::BinaryNode *&t) {  //  deletes all nodes in the subtree pointed to by t
    if(t != nullptr){   //  if t exists
        makeEmpty(t->left); //  delete left child
        makeEmpty(t->right);    //  delete right child
        delete t;   //  clean up t
    }
    t = nullptr;    //  set t to the nullptr
}

BET::BinaryNode *BET::clone(BET::BinaryNode *t) {   //  clones all nodes in the subtree pointed to by t
    if(t == nullptr){   //  no need to clone, if t is null
        return nullptr;
    }else{  //  clone
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
}

void BET::printPostfixExpression(BET::BinaryNode *n) {  //  outputs the corresponding postfix expression

    if(size(n) < 1){    //  Checks to see if the tree is empty before attempting a printout
        cout << "";
    }else{  //  Tree is not empty
        if((root->left == nullptr) && (root->right == nullptr)){    //  a node with no children, just print the node
            cout << (root->element) << endl;
        }else{  //  a node with children
            //  recursively call printPostFixExpression for children node prints
            printPostfixExpression(n->right);   //  right node
            printPostfixExpression(n->left); //  left node
            cout << (n->element) << " ";
        }
    }
}

size_t BET::size(BET::BinaryNode *t) {  //  returns the number of nodes in the subtree pointed to by t
    if(t == nullptr){   //  size is 0
        return 0;
    }else{  //  recursively return the sizes of the children nodes + 1
        return(size(t->left) + size(t->right) + 1);
    }
}

size_t BET::leaf_nodes(BET::BinaryNode *t) {    //  returns the number of leaf nodes in the subtree pointed to by t
    if(t == nullptr){   //  size of leaves are 0
        return 0;
    }
    if((t->left == nullptr) && (t->right == nullptr)){  //  if there are no children, return 1
        return 1;
    }else{  //  recursively return the number of left nodes + right nodes
        return(leaf_nodes(t->left) + leaf_nodes(t->right));
    }
}
















