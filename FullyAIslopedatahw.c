#include <stdio.h>
#include <stdlib.h>

typedef struct VizierRecord{
    char name[50];
    int start_year;     //sorting criteria
    int end_year;
    int income;
}VizierRecord;

typedef struct Node{
    VizierRecord* data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    int height;
}Node;

VizierRecord history[]={
    {" Lutfi Pasa ", 1539 , 1541 , 155000} ,
    {" Mahmud Pasa ", 1456 , 1468 , 4000000} , // <--- The Rival
    {" Piri Mehmed ", 1518 , 1523 , 145000} ,
    {" Candarli Ali ", 1387 , 1406 , 82000} ,
    {" Sokollu Mehmed ", 1565 , 1579 , 2000000} ,
    {" Pargali Ibrahim ", 1523 , 1536 , 3000000} , // <--- The Protagonist
    {" Koca Sinan ", 1580 , 1582 , 210000} ,
    {" Alaeddin Pasa ", 1320 , 1331 , 50000} ,
    {" Kemankes Mustafa ", 1638 , 1644 , 230000} ,
    {" Gedik Ahmed ", 1474 , 1477 , 115000} ,
    {" Koprulu Mehmed ", 1656 , 1661 , 260000} ,
    {" Ayas Mehmed ", 1536 , 1539 , 160000} ,
    {" Kuyucu Murad ", 1606 , 1611 , 220000} ,
    {" Candarli Halil ", 1364 , 1387 , 75000} ,
    {" Rustem Pasa ", 1544 , 1553 , 2800000} ,
    {" Merzifonlu Kara ", 1676 , 1683 , 290000} ,
    {" Semiz Ali ", 1561 , 1565 , 170000} ,
    {" Ferhad Pasa ", 1591 , 1592 , 190000} ,
    {" Nevsehirli Damat ", 1718 , 1730 , 240000} ,
    {" Koprulu Fazil ", 1661 , 1676 , 275000}
};

int max(int a, int b){
    return(a>=b) ? a:b;
}

int height(Node* node){
    if(!node)return 0;
    return node->height;
}

int balanceFactor(Node* node){
    if(!node)return 0;
    return height(node->left)-height(node->right);
}

Node* rotateRight(Node* node){
    Node* newnode=node->left;
    Node* temp=newnode->right;

    newnode->right=node;
    node->left=temp;

    newnode->parent=node->parent;
    node->parent=newnode;
    if(temp) temp->parent=node;

    node->height=1+max(height(node->left), height(node->right));
    newnode->height=1+max(height(newnode->left), height(newnode->right));

    return newnode;
}

Node* rotateLeft(Node* node){
    Node* newnode=node->right;
    Node* temp=newnode->left;

    newnode->left=node;
    node->right=temp;

    newnode->parent=node->parent;
    node->parent=newnode;
    if(temp) temp->parent=node;

    node->height=1+max(height(node->left), height(node->right));
    newnode->height=1+max(height(newnode->left), height(newnode->right));

    return newnode;
}

Node* insertAvlTree(Node* node, VizierRecord* pasha){

    if(!node){
        Node* newnode=(Node*)malloc(sizeof(Node));
        newnode->height=1;
        newnode->left=NULL;
        newnode->right=NULL;
        newnode->parent=NULL;
        newnode->data=pasha;
        return newnode;
    }

    if (node->data->start_year > pasha->start_year){
        node->left=insertAvlTree(node->left, pasha);
        if(node->left)node->left->parent=node;
    }else if(node->data->start_year < pasha->start_year){
        node->right=insertAvlTree(node->right, pasha);
        if(node->right)node->right->parent=node;
    }

    node->height=1+max(height(node->left), height(node->right));

    int balance=balanceFactor(node);

    if(balance>1 && pasha->start_year < node->left->data->start_year){
        return rotateRight(node);
    }
    if(balance<-1 && pasha->start_year > node->right->data->start_year){
        return rotateLeft(node);
    }
    if (balance>1 && pasha->start_year > node->left->data->start_year){
        node->left=rotateLeft(node->left);
        return rotateRight(node);
    }
    if(balance<-1 && pasha->start_year < node->right->data->start_year){
        node->right=rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}


void PrintPasha(Node* node){
    if(!node) return;

    PrintPasha(node->left);
    printf("%s\n", node->data->name);
    PrintPasha(node->right);
}

int main(){
    VizierRecord* pasha=&history[0];
    Node* root=NULL;

    for (int i = 0; i <20; i++){
        root=insertAvlTree(root, pasha++);
    }

    PrintPasha(root);

    return 0;
    
}
