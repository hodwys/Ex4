#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int weight;
int arrlenth;
pnode graph;
pnode head;

////////////Dijkstra/////////////

pdijkstra use_Dijkstra(pdijkstra head, int id) 
{
    while (head != NULL) 
    {
        if (head->node->id == id) {
            return head;
        }

        head = head->next;
    }
    return NULL;
}

void del_Dijk(pdijkstra dijkstra) 
{
    while (dijkstra != NULL)
    {
        pdijkstra temp = dijkstra;
        dijkstra = dijkstra->next;
        free(temp);
    }
}

pdijkstra min(pdijkstra head) 
{
    pdijkstra Node = NULL;

    while (head != NULL) 
    {
        if (!head->visit && head->weight < INFINITY && (Node == NULL || Node->weight < head->weight)) 
        {
            Node = head;
        }
        head = head->next;
    }
    if (Node != NULL) 
    {
        Node->visit = 1;
    }
    return Node;
}

int isEmpty(pnode p){
    if(p==NULL){
    return 1;
    }
    return 0;
}

// pnode GetNode(int id){
//     pnode cur = open;

//     return cur;
// }

pdijkstra RunDijkstra(pnode open, int src) 
{
    pdijkstra head = NULL;
    pdijkstra *n = &head;
    pnode temp = open;
    pnode cur = NULL;

    (temp) = (pnode) malloc(sizeof(pnode));
    if ((temp) == NULL) 
    {
        exit(0);
    }

    (cur) = (pnode) malloc(sizeof(pnode));
    if ((cur) == NULL) 
    {
        exit(0);
    }

    while(temp->id != src){
        temp = temp->next;
    }
    cur= temp;

    free(temp);

    while (!(isEmpty(open))) 
    {
        (*n) = (pdijkstra) malloc(sizeof(dijkstra));
        if ((*n) == NULL) 
        {
            exit(0);
        }

        (*n)->node = open;


        if (open->id == cur->id)
        {
            (*n)->weight = 0;
        } 
        else 
        {
            (*n)->weight = INFINITY;
        }
        (*n)->visit = 0;
        (*n)->next = NULL;
        n = &((*n)->next);
        open = open->next;
    }
    return head;
}

////////////////////SHORTEST PASH/////////////////

int shortest_Path(pnode head, int src, int dest) 
{
    pdijkstra dijkstraHead = RunDijkstra(head, src);
    pdijkstra temp = min(dijkstraHead);

    while (temp != NULL) 
    {
        pedge E_ind = temp->node->edges;

        while (E_ind != NULL) 
        {
            pdijkstra n = use_Dijkstra(dijkstraHead, E_ind->endpoint->id);

            int res = temp->weight + E_ind->weight;
            if (n->weight > res)
            {
                n->weight = res;
            }
            E_ind = E_ind->next;
        }
        temp = min(dijkstraHead);
    }
    int D = use_Dijkstra(dijkstraHead, dest)->weight;

    if (D == INFINITY)
    {
        D = -1;
    }
    del_Dijk(dijkstraHead);

    return D;
}

/////////////////TSP////////////////

void input_Array(int* fromArr,int* toArr, int arrLenght) 
{
    for (int i = 0; i < arrLenght; ++i) 
    {
        toArr[i] = fromArr[i];
    }
}

void swap(int* arr, int i, int j)
{
    int temp = arr[i];
    arr[i]= arr[j];
    arr[j] = temp;
}

void PermotitionOfArr(int* arr, int arrLength)
{
    int tempWeight = 0;
    for (int i = 0; i < arrLength-1; ++i) 
    {
        int D = shortest_Path(graph,arr[i], arr[i+1]);
        if (D == -1)
        {
            tempWeight = INFINITY;
            return;
        }
        tempWeight += D;
    }
    if (tempWeight < weight)
    {
        weight = tempWeight;
    }
}

void permotion( int start ,int* arr, int arrLength){
    if (start == arrLength -1 ){
        PermotitionOfArr(arr, arrLength);
        return;
    }
    for (int i = start; i < arrLength; ++i) {
        int* arrCopy = (int*)(calloc(arrLength, sizeof(int)));
        input_Array(arr,arrCopy,arrLength);
        swap(arrCopy,start, i);
        permotion(start + 1, arrCopy, arrLength);
        free(arrCopy);
    }
}

int TSP(pnode head)
{
    weight = INFINITY;
	arrlenth = -1;
    graph = head;
    scanf("%d", &arrlenth);
    int *arr = (int *) (calloc(arrlenth, sizeof(int)));

    for (int i = 0; i < arrlenth; i++) {
        scanf("%d", &arr[i]);
    }
    int *arrCopy = (int *) (calloc(arrlenth, sizeof(int)));
    input_Array(arr,arrCopy,arrlenth);
    permotion(0,arrCopy,arrlenth);
    free(arr);
    free(arrCopy);
    if (weight == INFINITY){
        weight = -1;
    }
    return weight;
}
