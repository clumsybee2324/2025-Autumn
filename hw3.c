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

int max(int a, int b){   //firstly, we have to write our helper functions
    return (a>=b)? a:b; //max will be our helper function
}

int height(Node* node){
    if(!node)return -1; //height is our second helper function
    return node->height;
}

int balanceFactor(Node* node){
    if(!node)return -1;
    return height(node->left)- height(node->right); //balance factor will our third helper function to insert
}

Node* rotateRight(Node* node){     //if our function left balanced, we should rotate it right          node
    Node* newnode=node->left;      //                                                             newnode
    Node* temp=newnode->right;     //                                                                temp -> we have that type of structure

    newnode->right=node;         //            newnode
    node->left=temp;            //                  node
                               //               temp -> we will have that type of function

    newnode->parent=node->parent;
    node->parent=newnode;
    if(temp)temp->parent=node;

    node->height=1+max(height(node->left), height(node->right));
    newnode->height=1+max(height(newnode->left), height(newnode->right)); //upgrade the height to calculate balance

    return newnode;
}

Node* rotateLeft(Node* node){  //    node
    Node* newnode=node->right; //        newnode   
    Node* temp=newnode->left; //      temp  -> the structure we have

    newnode->left=node;      //       newnode
    node->right=temp;        //     node   
                            //         temp  -> the structure we want to have
    newnode->parent=node->parent;
    node->parent=newnode;
    if(temp)temp->parent=node;

    node->height=1+max(height(node->left), height(node->right));
    newnode->height=1+max(height(newnode->left), height(newnode->right)); //we are updating the height
    return newnode;                                                 
}

Node* insertAvltree(Node* node, VizierRecord* pasha){
    if(!node){
        Node* newnode=(Node*)malloc(sizeof(Node));
        newnode->data=pasha;
        newnode->height=1;
        newnode->left=NULL;
        newnode->right=NULL;
        newnode->parent=NULL;
        return newnode;
    }
    if(pasha->start_year < node->data->start_year){
        node->left=insertAvltree(node->left, pasha);
        node->left->parent=node;
    }else if(pasha->start_year > node->data->start_year){
        node->right=insertAvltree(node->right, pasha);
        node->right->parent=node;
    }

    int balance=balanceFactor(node);
    node->height=1+max(height(node->left), height(node->right));

    if(balance>1 && pasha->start_year < node->left->data->start_year){
        return rotateRight(node);    //left-left condition
    }
    if(balance<-1 && pasha->start_year > node->right->data->start_year){
        return rotateLeft(node);    //right-right condition
    }
    if(balance>1 && pasha->start_year > node->left->data->start_year){
        node->left=rotateLeft(node->left);
        return rotateRight(node);  // left-right condition
    }
    if(balance<-1 && pasha->start_year < node->right->data->start_year){
        node->right=rotateRight(node->right);
        return rotateLeft(node);  //right-left condition
    }

    return node;
}

void PrintPasha(Node* node, int start, int window){
    if(!node)return;
    Node* current=node;
    while(node->data->start_year != start){
        if(start < node->data->start_year){
            node=node->left;
        }else if(start > node->data->start_year){
            node=node->right;
        }
    }
    printf("--- QUERY: %d (%s) --- [TARGET]\n", start, node->data->name);
    printf("> %s (%d Akce)\n", node->data->name, node->data->income);
    printf("[NEIGHBOR COMPARISON (Window:%d)]\n", window);

    Node* pre=NULL;
    if(node->left){    //if we have left node we have to start from there
        pre=node->left;   //our starting point
        while(pre->right){   //we have to go to right side because our aim to reach right of left
            pre=pre->right;
        }
    }else{
        Node* current=node;    //if we don't have left node we need to reach the parent node
        pre=node->parent; //we need a starting point same as above
        while(pre !=NULL && current==pre->left){    //from the leftest, we are going to parents of the pre
            current=pre;
            pre=pre->parent;
        }
    }

    Node* suc=NULL; //similar as pre, we have to reach left of right
    if(node->right){   // we are going to right
        suc=node->right;
        while (suc->left){  //and left from right
            suc=suc->left;
        }    
    }else{
        Node* current=node;
        suc=node->parent; //if we don't have right node to reach right, we have to go to the parents same as pre
        while(suc !=NULL && current==suc->right){ //we are going to the parent node
            current=suc;
            suc=suc->parent;
        }
    }

    if(pre){
        printf("(<<) PREDECESSOR: %s (%d Akce)\n", pre->data->name, pre->data->income);
    }
    if(suc){
        printf("(>>) SUCCESSOR: %s (%d Akce)\n", suc->data->name, suc->data->income);
    }

}

int main(){
    VizierRecord* pasha=&history[0];
    Node* root=NULL;

    for(int i=0; i<20; i++){
        root=insertAvltree(root, pasha++);
    }
    PrintPasha(root, 1523,1);
    return 0;
}
