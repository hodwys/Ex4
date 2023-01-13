#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int weight;
int arrlenth;
pnode graph;

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
            // relax

            int relax(temp, n, E_ind);
        }
        // faind the next
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



// int dijkstra(int start, int end){
//     //restart the graph
//     pNode temp = head;
//     while (temp){
//         temp->weight = MAX;
//         temp->parent = NULL;
//         temp->visited = 0;
//         temp = temp->next;
//     }
//     int min = MAX;
//     int relax1 = MAX;    
//     pNode n_start = GetNode(start); //find the node with start id
//     n_start->weight = 0; 
//     pNode cur = n_start;
//     while (!(isEmpty(cur))){
//         if(cur->visited == 0){
//             if(cur->nodeId == end){
//                 int weight = cur->weight;
//                 while (!(isEmpty(cur))){
                
//                 pNode temp = cur;
//                 cur = cur->next;
//                 free(temp);    
//                 }
                
//                 return weight;
//             }
//             cur->visited = 1;
//             pEdge e = cur->edges;
//             while (e){
//                relax1 = relax(GetNode(cur->nodeId), GetNode(e->dest->nodeId), e);
//                if(relax1 < min){
//                 min = relax1;
//                }

//                 e = e->next;
//             }
//             pNode temp = cur->next;
//             while(temp){
//                 if(temp->weight == min){
//                     free(cur);
//                     pNode cur = temp;
//                     free(temp);
//                     min=MAX;
//                 }
//                 temp = temp->next;
            
//             }
//         }
    
//     }
// return 0;
// }




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
