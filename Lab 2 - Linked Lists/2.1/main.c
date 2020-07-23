#include <stdio.h>
#include <stdlib.h>
#define NULL 0

typedef struct node
{
    int truck_id;
    struct node* next;
}Truck;

typedef struct SLList
{
    struct node* first, * last;
    int length;
}ListT;

ListT* road;
ListT* garage;

void initList(ListT** listPtr)
{
    (*listPtr)->first = NULL;
    (*listPtr)->last = NULL;
    (*listPtr)->length = 0;
}

Truck* createTruck(int key)
{
    Truck* p = (Truck*)malloc(sizeof(Truck));
    if(p)
    {
        p->truck_id = key;
        p->next = NULL;
    }
    return p;
}

int insertAtFront(ListT** listPtr, int key)
{
    Truck* p = createTruck(key);
    p->next = NULL;
    if((*listPtr))
    {
        p->next = (*listPtr)->first;
        if((*listPtr) == NULL)
        {
            (*listPtr)->last = p;
        }
        (*listPtr)->first = p;
        (*listPtr)->length++;
        return 1;
    }
    return 0;
}

void onRoad(int key)
{
    insertAtFront(&road, key);
}

Truck* find(ListT* listPtr, int givenKey)
{
    Truck* p;
    p = listPtr->first;
    while(p != NULL)
    {
        if(p->truck_id == givenKey)
        {
            return p;
        }
        else
        {
            p = p->next;
        }
    }
    return NULL;
}

Truck* deleteFirst(ListT** listPtr)
{
    Truck *p;
    if((*listPtr)->first != NULL)
    {
        p = (*listPtr)->first;
        (*listPtr)->first = (*listPtr)->first->next;
        (*listPtr)->length--;
        if((*listPtr)->first == NULL)
        {
            (*listPtr)->last = NULL;
        }
        return p;
    }
    return NULL;
}

void showTrucks(ListT* listPtr)
{
    Truck* p;
    p = listPtr->first;
    if(p == NULL)
        printf("None");
    while(p != NULL)
    {
        printf("%d ", p->truck_id);
        p = p->next;
    }
    printf("\n");
}

void enterGarage(int key)
{
    if(find(road, key) != NULL)
    {
        insertAtFront(&garage, road->first->truck_id);
        deleteFirst(&road);
    }
    else
    {
        printf("Error:%d is not on road", key);
    }
    printf("\n");
}

void exitGarage(int key)
{
    if(find(garage, key) != NULL && garage->first->truck_id == key)
    {
        insertAtFront(&road, garage->first->truck_id);
        deleteFirst(&garage);
    }
    else
    {
        if(find(garage, key) == NULL)
            printf("Error:%d is not in garage.", key);
        else
            if(garage->first->truck_id != key)
            printf("Error:%d is not first.", key);
    }
    printf("\n");
}

int main()
{
    road = (ListT*)malloc(sizeof(ListT));
    garage = (ListT*)malloc(sizeof(ListT));
    initList(&road);
    initList(&garage);
    onRoad(2);
    onRoad(5);
    onRoad(10);
    onRoad(22);
    showTrucks(road);
    showTrucks(garage);
    enterGarage(2);
    showTrucks(road);
    showTrucks(garage);
    enterGarage(10);
    enterGarage(25);
    exitGarage(10);
    exitGarage(2);
    showTrucks(road);
    showTrucks(garage);
    return 0;
}
