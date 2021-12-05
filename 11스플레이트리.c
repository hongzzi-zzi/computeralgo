#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode
{
   int key;
   struct TreeNode* parent, *left, *right;
}TreeNode;

typedef struct{
    TreeNode* root;
}TreeType;

void rightRotate(TreeType *T,TreeNode *x,TreeNode *y){

    TreeNode *T0, *T1,*T2,*p;
    
    p=y->parent;
    T0=x->left;
    T1=x->right;
    T2=y->right;

    y->parent=x;
    x->parent=p;

    if(x->parent==NULL)
        T->root=x;
    
    x->left=T0;
    x->right=y;
    y->left=T1;
    y->right=T2;
}

void leftRotate(TreeType *T, TreeNode *x, TreeNode*y){

    TreeNode *T0, *T1, *T2, *p;

    p=y->parent;
    T0=y->left;
    T1=x->left;
    T2=x->right;

    y->parent-x;
    x->parent=p;

    if(x->parent==NULL)
        T->root=x;

    x->left=y;
    x->right=T2;
    y->left=T0;
    y->right=T1;
}

int main(){

    return 0;
}