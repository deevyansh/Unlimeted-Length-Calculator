/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

#include <iostream>
using namespace std;
//Write your code below this line

Parser::Parser(){
    vector<ExprTreeNode *>v1;
    symtable=new SymbolTable;
    expr_trees=v1;
    last_deleted=0;
}


ExprTreeNode* parse1(vector<string> code, int left, int right, SymbolTable* s1){
    if ((right-left)==1){
        if (isdigit(code[left][0])){
            int r2=stoi( code[left]);
            ExprTreeNode* t1= new ExprTreeNode("VAL",r2);
            return (t1);}
        else{
            ExprTreeNode *t1 =new ExprTreeNode(code[left],0);
            return (t1);
        }
    }
    else{
        int temp=0;
        for (int i = left + 1; i < static_cast<int>(code.size() - 1); i++) {
            if (code[i]=="("){
                temp++;
            }
            else if (code[i]==")"){
                temp--;
            }
            else if (code [i]=="+" && temp==0){
                ExprTreeNode* root= new ExprTreeNode("ADD",0);
                root->left=parse1(code, left+1, i, s1);
                root->right=parse1(code,i+1,right-1,s1);
                return root;
            }
            else if (code [i]=="-" && temp==0){
                ExprTreeNode* root= new ExprTreeNode("SUB",0);
                root->left=parse1(code, left+1, i, s1);
                root->right=parse1(code,i+1,right-1,s1);
                return root;
            }
            else if (code [i]=="*" && temp==0){
                ExprTreeNode* root= new ExprTreeNode("MUL",0);
                root->left=parse1(code, left+1, i, s1);
                root->right=parse1(code,i+1,right-1,s1);
                return root;
            }
            else if (code [i]=="/" && temp==0){
                ExprTreeNode* root= new ExprTreeNode("DIV",0);
                root->left=parse1(code, left+1, i, s1);
                root->right=parse1(code,i+1,right-1,s1);
                return root;
            }
        }
        return NULL;
    }
    return NULL;
}



void Parser::parse(vector<string> expression){
    if (expression[0]!="del"){
        ExprTreeNode*root= new ExprTreeNode("EQU",0);
        ExprTreeNode*r2= new ExprTreeNode(expression[0],0);
        root->left= r2;
        root->right = parse1(expression, 2, static_cast<int>(expression.size()), symtable);
        expr_trees.push_back(root);
        return ;}
    else{
        symtable->remove(expression[2]);
    }
}

Parser::~Parser(){
    delete symtable;
    expr_trees.clear();
}


//int main(){
//    Parser E;
//    vector<std::string> v1 = {"ret", ":=", "(", "2","+","3",")"};
//    vector<std::string> v2 = {"ap2", ":=", "(", "ap1", "-", "(", "4", "/", "3", ")", ")"};
//    vector<std::string> v3 = {"ap3", ":=", "(", "ap2", "+", "(", "4", "/", "5", ")", ")"};
//    vector<std::string> v4 = {"ap4", ":=", "(", "ap3", "-", "(", "4", "/", "7", ")", ")"};
//    vector<std::string> v5 = {"ap5", ":=", "(", "ap4", "+", "(", "4", "/", "9", ")", ")"};
//    vector<std::string> v6 = {"ap6", ":=", "(", "ap5", "-", "(", "4", "/", "11", ")", ")"};
//    vector<std::string> v7 = {"ap7", ":=", "(", "ap6", "+", "(", "4", "/", "13", ")", ")"};
//    E.parse(v1);
//    E.parse(v2);
//    E.parse(v3);
//    E.parse(v4);
//    E.parse(v5);
//    E.parse(v6);
//    E.parse(v7);
//    cout<<endl;
//    cout<<E.expr_trees[0]->type;
//    cout<<E.expr_trees[0]->left->type;
//    cout<<E.expr_trees[0]->left->id;
//    cout<<E.expr_trees[0]->right->type;
//    cout<<E.expr_trees[0]->right->num;
//    cout<<E.expr_trees[0]->left->id;
//    cout<<endl;
//    cout<<E.expr_trees[1]->type;
//    cout<<E.expr_trees[1]->left->type;
//    cout<<E.expr_trees[1]->right->type;
//    cout<<E.expr_trees[1]->right->left->id;
//    return 0;
//}
