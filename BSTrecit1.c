#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int num;
}TreeNode;

typedef struct BSTree{
    TreeNode* treenode;
    struct BSTree* left;
    struct BSTree* right;
}BSTree;

TreeNode initnode[]={40, 20, 60, 10, 30, 50, 70};

BSTree* insertItem(BSTree* node, TreeNode* nextnode){
    if (!node){
        BSTree* newnode=(BSTree*)malloc(sizeof(BSTree));
        newnode->left=NULL;
        newnode->right=NULL;
        newnode->treenode=nextnode;
        return newnode;
    }

    if(node->treenode->num > nextnode->num){
        node->left=insertItem(node->left, nextnode);
    }else if(node->treenode->num < nextnode->num){
        node->right=insertItem(node->right, nextnode);
    }
    
    return node;
}

BSTree* addNewNode(BSTree* node, int newnum){

    BSTree* newnode=(BSTree*)malloc(sizeof(BSTree));
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->treenode->num=newnum;

    if (node->treenode->num > newnode->treenode->num){
        node->left=addNewNode(node->left, newnum);
    }else if(node->treenode->num < newnode->treenode->num){
        node->right=addNewNode(node->right, newnum);
    }
    
    return node;
}

BSTree* deleteNode(BSTree* node, int deletenum){
    if(!node) return NULL; //baştan node bulunamadı
}

int main(){

    BSTree* root= NULL;
    int size= sizeof(initnode)/sizeof(initnode[0]);
    TreeNode* mynode=&initnode[0];

    for (int i = 0; i < size; i++){
        root=insertItem(root, mynode++);
    }

    root=addNewNode(root, 5);
    root=addNewNode(root, 25);
    root=addNewNode(root, 65);

    root=deleteNode(root, 10);
    
    return 0;
}
