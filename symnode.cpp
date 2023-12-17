/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
#include <iostream>
using namespace std;
//Write your code below this line

SymNode::SymNode(){
}

SymNode::SymNode(string k){
    key=k;
    height=0;
    address=-1;
    par=NULL;
    left=NULL;
    right=NULL;
}

int max(int a, int b){
    if (a>b){
        return a;
    }
    else{
        return b;
    }
}

void heightdedo(SymNode* n){
    if (n->left==NULL && n->right==NULL){
        n->height=0;
    }
    else if (n->left==NULL){
        n->height=n->right->height+1;
    }
    else if (n->right==NULL){
        n->height=n->left->height+1;
    }
    else{
        n->height=1+max(n->left->height,n->right->height);}
}


SymNode* SymNode::LeftLeftRotation(){
    SymNode*root= this;
    SymNode* newparent=root->right;
    root->right=newparent->left;
    if (newparent->left!=NULL){
        newparent->left->par=newparent;
    }
    newparent->par=root->par;
    if (root->par!=NULL){
        if (root->par->left == root) {
            root->par->left = newparent;}
        else {
            root->par->right = newparent;}
    }
    root->par=newparent;
    newparent->left=root;
    heightdedo(root);
    heightdedo(newparent);
    SymNode* n =newparent;
    while (n!=NULL){
        heightdedo(n);
        n=n->par;
    }
    return (newparent);
}

SymNode* SymNode::RightRightRotation(){
    SymNode*root= this;
    SymNode* newparent= root->left;
    if (newparent->right!=NULL){
        newparent->right->par=root;}
    root->left=newparent->right;
    newparent->par=root->par;
    if (root->par!=NULL){
        if (root->par->left == root) {
            root->par->left = newparent;}
        else {
            root->par->right = newparent;}
    }
    newparent->right=root;
    newparent->right->par=newparent;
    heightdedo(root);
    heightdedo(newparent);
    SymNode* n =newparent;
    while (n!=NULL){
        heightdedo(n);
        n=n->par;
    }
    return  (newparent);
}

SymNode* SymNode::RightLeftRotation(){
    this->left=this->left->LeftLeftRotation();
    return this->RightRightRotation();
}

SymNode* SymNode::LeftRightRotation(){
    this->right=this->right->RightRightRotation();
    return this->LeftLeftRotation();
}

SymNode::~SymNode(){
    if (left != NULL) {
           delete left;
       }
    if (right != NULL) {
           delete right;
       }
    if (par!=NULL){
        delete  par;
    }
}

//int main(){
//    SymNode*A =new SymNode("a");
//    SymNode*B=new SymNode("b");
//    SymNode*C= new SymNode("c");
//    SymNode*D =new SymNode("d");
//    SymNode*E=new SymNode("e");
//    A->left=B;
//    B->left=C;
//    B->par=A;
//    C->par=B;
//    A->par=nullptr;
//    A->height=2;
//    B->height=1;
//    C->height=0;
//    B->right=D;
//    D->par=B;
//    A->right=E;
//    E->par=A;
//    B=A->LeftLeftRotation();
//    cout<<B->key;
//    cout<<B->left->key;
//    cout<<B->right->key;
//    cout<<B->height;
//    cout<<A->height;
//    cout<<C->height;
//    cout<<A->right->left->key;
//    cout<<A->right->right->key;
//    A->right=B;
//    B->par=A;
//    B->right=C;
//    C->par=B;
//    B->left=D;
//    D->par=B;
//    A->left=E;
//    E->par=A;
//    B=A->RightRightRotation();
//    cout<<B->key;
//    cout<<B->left->key;
//    cout<<B->right->key;
//    cout<<B->left->right->key;
//    cout<<A->right->key;
//    cout<<C->par->key;
//    cout<<(C->left==nullptr);
//    cout<<(C->right==nullptr);
//    cout<<B->left->left->key;
//    A->left=B;
//    B->par=A;
//    B->right=C;
//    C->par=B;
//    C=A->LeftRightRotation();
//    cout<<C->left->key;
//    cout<<C->right->key;
//    cout<<(B->par->key);
//    cout<<(B->left==nullptr);
//    cout<<(B->right==nullptr);
//    cout<<(A->left==nullptr);
//    cout<<(A->right==nullptr);
    
    
//
//    SymNode* b= new SymNode("b");
//    SymNode* y =new SymNode("y");
//    SymNode* x=new SymNode("x");
//    SymNode* z =new SymNode("z");
//    b->right=y;
//    y->par=b;
//    y->right=z;
//    z->par=y;
//    y->left=x;
//    x->par=y;
//    y->height=1;
//    b->height=2;
//    x->height=0;
//    b->RightLeftRotation() ;
//    cout<<b->height;
//    cout<<y->height;
//    cout<<x->height;
//    return 0;
//}
