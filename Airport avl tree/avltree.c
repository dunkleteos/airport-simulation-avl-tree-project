#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"


struct AVLNode* CreateTree(void){    //I used CNG213 Worksheet 10 Template.c for these functions
    return NULL;


}

struct AVLNode* MakeEmptyTree(struct AVLNode* t)
{
    if (t != NULL)
    {
        MakeEmptyTree(t->left);
        MakeEmptyTree(t->right);
        free(t);
    }
    return NULL;

}

struct AVLNode* InsertFlight(struct AVLNode* t, struct Flight* flight){   //I used InsertElement(int val, AVLTree t)
            if (t == NULL)
            {
                t = (struct AVLNode*)malloc(sizeof(struct AVLNode));
                if (t == NULL)
                    printf("Out of memory space!!!\n");
                else
                {
                    t->data = flight;
                    t->left = t->right = NULL;
                    t->height = 0;
                    flight->next = NULL;
                }
            }
            else if (strcmp(flight->destination, t->data->destination) < 0)
            {
                t->left=InsertFlight(t->left, flight);
                if (AVLTreeHeight(t->left)- AVLTreeHeight(t->right) == 2){
                    if (strcmp(flight->destination,t->left->data->destination)< 0)
                        t=SingleRotateWithRight(t);
                    else
                        t=DoubleRotateWithLeft(t);
                }
            }
            else if(strcmp(flight->destination,t->data->destination) > 0)
            {
                t->right = InsertFlight(t->right,flight);
                if (AVLTreeHeight(t->right)- AVLTreeHeight(t->left) == 2)
                {
                    if (strcmp(flight->destination,t->right->data->destination) > 0)
                        t=SingleRotateWithLeft(t);
                    else
                        t=DoubleRotateWithRight(t);}
            }
            else{
                flight->next=t->data;
                t->data = flight;
                return t;
            }
            t->height=Max(AVLTreeHeight(t->left),AVLTreeHeight(t->right)) + 1;
            return t;


}

struct AVLNode*  SingleRotateWithRight(struct AVLNode*  k2)
{
    struct AVLNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = Max(AVLTreeHeight(k2->left),AVLTreeHeight(k2->right)) + 1;
    k1->height = Max(AVLTreeHeight(k1->left),k2->height) + 1;
    return k1;



}

struct AVLNode*  SingleRotateWithLeft(struct AVLNode*  k1)
{
    struct AVLNode* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = Max(AVLTreeHeight(k1->left),AVLTreeHeight(k1->right))+ 1;
    k2->height = Max(AVLTreeHeight(k2->right),k1->height) + 1;
    return k2;


}

struct AVLNode*  DoubleRotateWithLeft(struct AVLNode*  k3)
{
    k3->left =SingleRotateWithLeft(k3->left);
    return SingleRotateWithRight(k3);


}

// right and left rotation
struct AVLNode*  DoubleRotateWithRight(struct AVLNode* k3)
{
    k3->right= SingleRotateWithRight(k3->right);
    return SingleRotateWithLeft(k3);
}

int Max(int x, int y)
{
    if (x >= y) return x;
    else return y;
}

int AVLTreeHeight(struct AVLNode* t)
{
    if(t==NULL) return -1;
    return t->height;
}

void DisplayTree(struct AVLNode* t){
    if (t!= NULL){  DisplayTree(t->left);

        struct Flight *f = t->data;
        while (f!= NULL){
            PrintFlightDetails(f);
            f= f->next;}
        DisplayTree(t->right);
    }
}

void PrintFlightDetails(struct Flight* flight){
    printf("Destination:%s\n",flight->destination);
    printf("Airline:%s\n",flight->airline);
    printf("Type:%c\n",flight->type);
    printf("Date:%s\n", flight->date);
    printf("Miles:%d\n",flight->miles);
}

struct Flight* FindDestination(struct AVLNode *t, char *destination)
        {
    if(t== NULL)return NULL;

    int cmp = strcmp(destination,t->data->destination);
    if (cmp == 0)
        return t->data;
    else if (cmp < 0)
        return FindDestination(t->left,destination);
    else
        return FindDestination(t->right,destination);
}