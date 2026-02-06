#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

struct AVLNode* loadFlights(char *fileName);
struct AVLNode* insertFlight(struct AVLNode* t, char *destination, char *airline, char type, char *date, int miles);
void infoFlights(struct AVLNode* t, char *destination);
void displayFlights(struct AVLNode* t);
struct Flight* findFurthestDestination(struct AVLNode* t);
void FurthestDestinations(struct AVLNode* t, struct Flight* highestMilesFlight);

int main (int argc, char **argv){

    struct AVLNode* myTree = NULL;
    int menuOption, flag = 1;

    if(argc == 1){
        printf("Please provide a file name: ");
        return 0;
    }

    myTree = loadFlights(argv[1]);

    printf("Welcome to data analysis @ Istanbul Airport\n");

    while (flag){
        printf("\n-------Menu-------\n"
               "(1)Insert flight\n"
               "(2)Display the full index of flights\n"
               "(3)Display the details of the flight\n"
               "(4)Display the furthest destination\n"
               "(5)Exit\n"
               "Enter your option:");
        scanf("%d", &menuOption);

        switch (menuOption) {

            case 1:{
                char destination[50], airline[50], type, date[11];
                int miles;

                printf("Please enter flight details:\n");
                printf("Destination: ");
                scanf(" %s", destination);
                printf("Airline: ");
                scanf(" %s", airline);
                printf("Type: ");
                scanf(" %c", &type);
                printf("Date: ");
                scanf(" %s", date);
                printf("Miles: ");
                scanf("%d", &miles);

                myTree = insertFlight(myTree, destination, airline, type, date, miles);
                printf("%s %s has been added successfully.\n", airline, destination);
                break;
            }
            case 2:{
                displayFlights(myTree);
                break;
            }
            case 3:{
                char destination[50];
                printf("Destination: ");
                scanf(" %s", destination);
                infoFlights(myTree,destination);
                break;
            }
            case 4:{
                printf("Detailed information of the furthest destination:\n");
                FurthestDestinations(myTree, findFurthestDestination(myTree));
                break;
            }
            case 5: {
                flag = 0;
                break;
            }
            default:{
                printf("Option %d can't be recognized.\n", menuOption);
            }
        }
    }

    myTree = MakeEmptyTree(myTree);
    return 0;
}

struct AVLNode* insertFlight(struct AVLNode* t, char *destination, char *airline, char type, char *date, int miles) {
    struct Flight *f = (struct Flight*)malloc(sizeof(struct Flight));
    strcpy(f->destination,destination);
    strcpy(f->airline,airline);
    f->type=type;
    strcpy(f->date,date);
    f->miles=miles;
    f->next=NULL;

    return InsertFlight(t,f);


}

struct AVLNode* loadFlights(char *fileName){


    FILE *fp = fopen(fileName,"r");
    if(fp==NULL){
        printf("File couldn't be opened.\n");
        return NULL;}


    struct AVLNode *tree =CreateTree();
    char line[200];
    while (fgets(line,sizeof(line),fp)){
        char destination[50], airline[50], date[11];
        char type;
        int miles;

        // Parse each line from file into flight fields (Destination, Airline, Type, Date, Miles)
        // I used sscanf, a standard C function for formatted string reading.

        sscanf(line, "%[^;];%[^;];%c;%[^;];%d",destination, airline, &type, date, &miles);
        tree=insertFlight(tree, destination, airline, type, date, miles);
    }
    fclose(fp);
    return tree;


}

void displayFlights(struct AVLNode* t){
    if (t != NULL)
    {
        displayFlights(t->left);

        struct Flight *f = t->data;
        while (f != NULL)
        {
            printf("%s %s %c %s %d\n",f->destination,f->airline,f->type,f->date,f->miles);
            f =f->next;
        }
        displayFlights(t->right);



    }


}

void infoFlights(struct AVLNode* t, char *destination){    // Searching in AVL: O(log n), printing flights in the node: O(k)
    struct Flight *f = FindDestination(t, destination);    // Total: O(log n + k)
                                                           // Improvement: Use a BST/AVL instead of linked list for faster search inside the node
    if (f == NULL)
    {
        printf("There is no available flight whose name is %s.\n",destination);
        return;

    }
    while (f != NULL)
    {

        printf("%s %s %c %s %d\n",f->destination,f->airline,f->type,f->date,f->miles);
        f = f->next;
    }


}

struct Flight* findFurthestDestination(struct AVLNode* t){
    if(t==NULL) return NULL;

    struct Flight *maxLeft= findFurthestDestination(t->left);
    struct Flight *maxRight= findFurthestDestination(t->right);

    struct Flight *current= t->data;
    struct Flight *maxHere=current;

    while (current!=NULL)
    {
        if (current->miles> maxHere->miles)
            maxHere=current;
        current=current->next;

    }
    struct Flight *max= maxHere;
    if (maxLeft && maxLeft->miles > max->miles)
        max = maxLeft;
    if (maxRight && maxRight->miles > max->miles)
        max = maxRight;

    return max;



}

void FurthestDestinations(struct AVLNode* t, struct Flight* highestMilesFlight){
    if (t == NULL || highestMilesFlight == NULL)
        return;                                              // Traversing entire tree: O(n), scanning linked lists too → O(n + total_flights)
                                                             // Improvement: Use a max-heap or additional index on miles for faster access
    FurthestDestinations(t->left, highestMilesFlight);

    struct Flight *f = t->data;
    while (f != NULL)
    {

        if (f->miles == highestMilesFlight->miles)
        {
            printf("%s %s %c %s %d\n",f->destination,f->airline,f->type,f->date,f->miles);}
        f = f->next;

    }
    FurthestDestinations(t->right, highestMilesFlight);


}
