// Created by Tyler Starling on 6/27/2021.
// COP 4530
// BET class header file

#ifndef COP4530_PROGRAM_4_BET_H
#define COP4530_PROGRAM_4_BET_H
#include <iostream>
#include <string>
using namespace std;
class BET{

    public:
        BET();  //  default constructor
        BET(const string& postfix);    //   1-parameter constructor, where parameter is a string containing a postfix expression
        BET(const BET&);    //  copy constructor
        ~BET(); //  destructor
        bool buildFromPostfix(const string& postfix);   //  builds an expression tree based on the passed in postfix string
        const BET & operator=(const BET &); //  assignment operator
        void printInfixExpression();    //  prints out the infix expression; uses private recursive function to help
        void printPostfixExpression();  //  prints out the postfix expression; uses private recursive function to help
        size_t size();  //  returns the number of nodes in the tree; uses the private recursive function
        size_t  leaf_nodes();   //  returns the number of leaf nodes in the tree; uses the private recursive function
        bool empty();   //  returns true if the tree is empty; false otherwise
    private:
        struct BinaryNode {

            string element;
            BinaryNode *left;
            BinaryNode *right;

            BinaryNode(string theElement = string{}, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr)
                    : element{move(theElement)}, left{lt}, right{rt} {}
        };

        BinaryNode *root;   //  pointer root of the tree

        void printInfixExpression(BinaryNode *n);   //  prints the corresponding infix expression
        void makeEmpty(BinaryNode* &t); //  deletes all nodes in the subtree pointed to by t
        BinaryNode * clone(BinaryNode *t);  //  clones all nodes in the subtree pointed to by t; can be called by functions like assignment operator=
        void printPostfixExpression(BinaryNode *n); //  prints the corresponding postfix expression
        size_t size(BinaryNode *t); //  returns the number of nodes in the subtree pointed to by t
        size_t leaf_nodes(BinaryNode *t);   //  returns the number of leaf nodes in the subtree pointed to by t
};

#endif //COP4530_PROGRAM_4_BET_H
