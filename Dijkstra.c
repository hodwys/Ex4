#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int weight;
int arrlenth;
pnode graph;
int mini = INFINITY;

////////////Dijkstra/////////////



pnodeD getD(pnodeD head, int id) 
{
    while (!(isEmpty(head))) 
    {
        if (head->node->id == id) {
            return head;
        }

        head = head->next;
    }
    return NULL;
}


pnodeD getD_wet(pnodeD head, int wet) 
{
    while (head != NULL) 
    {
        if(head->visit==0){
            if (head->weight == wet) {
                head->visit =1;
                return head;
            }
        }
        head = head->next;
    }
    return NULL;
}



void deleteD(pnodeD dijkstra) 
{
    while (dijkstra != NULL)
    {
        pnodeD temp = dijkstra;
        dijkstra = dijkstra->next;
        free(temp);
    }
}

int isEmpty(pnode p){
    if(p==NULL){
    return 1;
    }
    return 0;
}

int isEmpty_d(pnodeD p){
    if(p==NULL){
    return 1;
    }
    return 0;
}

pnode GetNode2( int id,pnode head ){
    pnode cur =head;
    while (!(isEmpty(cur)))
    {
        if(cur->id == id){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}


int relax(pnodeD src,pnodeD dest, pedge e)
{
    
    int wEdge = e->weight;
    int wSrc = src->weight;
    int wDest = dest->weight;
    if (wDest > wSrc + wEdge)
    {
        dest->weight = wSrc + wEdge;
       // dest->parent = src;
    }
return dest->weight;
}

pnodeD RunDijkstra(pnode open, int src) 
{
    pnodeD head = NULL;
    pnodeD *n = &head;

    while (!(isEmpty(open))) 
    {
        (*n) = (pnodeD) malloc(sizeof(nodeD));
        if ((*n) == NULL) 
        {
           return NULL;
        }

        (*n)->node = open;

        (*n)->visit = 0;
        (*n)->next = NULL;
        n = &((*n)->next);
        open = open->next;
        (*n)->weight = INFINITY;
    }
        
        if (open == GetNode2(src, open))
        {
            (*n)->weight = 0;
        } 
    return head;
}

////////////////////SHORTEST PASH/////////////////

int shortest_Path(pnode head, int src, int dest) 
{
    // GET SRC
    pnodeD dijkstraHead = RunDijkstra(head, src);

    pnodeD temp = getD_wet(dijkstraHead,0);


     while (!(isEmpty(temp))) 
    {
        pedge E_ind = temp->node->edges;

        while (E_ind != NULL) 
        {
            //faind dest
           pnodeD n = getD(dijkstraHead, E_ind->endpoint->id);
        
            // apdayt the min 
            int relax1 = relax(temp, n, E_ind);
             if(relax1 < mini){
                  mini = relax1;
              }
            E_ind = E_ind->next;

        }

        // find the node of min
        temp = getD_wet(dijkstraHead ,mini);
        //temp->visit=1;
        mini = INFINITY; 
        // temp = ..
       // temp = min(dijkstraHead);
    }
    int D = getD(dijkstraHead, dest)->weight;

    if (D == INFINITY)
    {
        D = -1;
    }
   deleteD(dijkstraHead);

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
