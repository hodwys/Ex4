#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int weight;
int arrlenth;
pnode graph;
int mini = INFINITY;

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

pdijkstra use_Dijkstra_wet(pdijkstra head, int wet) 
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



void del_Dijk(pdijkstra dijkstra) 
{
    while (dijkstra != NULL)
    {
        pdijkstra temp = dijkstra;
        dijkstra = dijkstra->next;
        free(temp);
    }
}
// find min
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

int isEmpty_d(pdijkstra p){
    if(p==NULL){
    return 1;
    }
    return 0;
}



int relax(pdijkstra src,pdijkstra dest, pedge e)
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

pdijkstra RunDijkstra(pnode open, int src) 
{
    pdijkstra head = NULL;
    pdijkstra *n = &head;

    while (!(isEmpty(open))) 
    {
        (*n) = (pdijkstra) malloc(sizeof(dijkstra));
        if ((*n) == NULL) 
        {
            exit(0);
        }

        (*n)->node = open;
        if (open->id == src)
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
    // GET SRC
    pdijkstra dijkstraHead = RunDijkstra(head, src);

    // find min or start with the src.. temp = src

   // pdijkstra temp = min(dijkstraHead);

    //dijkstraHead->visit=1;
    //pdijkstra temp = dijkstraHead;

    pdijkstra temp = NULL;
    pdijkstra *n = &head;
    (*n)->node =GetNode(src);
    temp->visit=1; 
       
     while (temp != NULL) 
    {
        pedge E_ind = temp->node->edges;

        while (E_ind != NULL) 
        {
            //faind dest
            pdijkstra n = use_Dijkstra(dijkstraHead, E_ind->endpoint->id);
        
            // apdayt the min 
            int relax1 = relax(temp, n, E_ind);
             if(relax1 < mini){
                  mini = relax1;
              }
            E_ind = E_ind->next;

        }

        // find the node of min
        temp = use_Dijkstra_wet(dijkstraHead ,mini);
        //temp->visit=1;
        mini = INFINITY; 
        // temp = ..
       // temp = min(dijkstraHead);
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
