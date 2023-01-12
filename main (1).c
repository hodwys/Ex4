#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    pnode temp = NULL;
    pnode *head = &temp;
    char prog;
    char cp;
    int v = 0;
    int src = 0;


    
    while (scanf("%c", &prog) != EOF){
 
        if(prog == 'A'){
            scanf("%d", &v);
            *head =  creat_graph(v);
            
           int c = scanf("%c", &cp);
            
            while(c != 0){
            c = scanf("%c", &cp);    
                if(cp == 'n'){
                scanf("%d",&src);
                add_adge(head,src);
                
                }
                else
                {
                    break;
                }
                

            }
            // print_graph(*head);
            
            prog = cp;
        }

        if(prog == 'B')
        {
            add_node(head);
            // print_graph(*head);
            continue;
        }
        if(prog == 'D')
        {
            del_node(head);
            // print_graph(*head);
            continue;
        }
        if(prog == 'S')
        {
            // shortsPath(*head);
            int src = -1, dest = -1;
            scanf("%d %d", &src, &dest);
            int dis = shortest_Path(*head, src, dest);
            printf("Dijsktra shortest path: %d ",dis);
            printf("\n");
            continue;
        }
        if(prog == 'T')
        {
            int tsp = TSP(*head);
            printf("TSP shortest path: %d ",tsp);
            printf("\n");
            continue;
        }
       
    
    }
    freeGraph(head);
}