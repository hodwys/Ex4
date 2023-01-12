#ifndef GRAPH_
#define GRAPH_
#define INFINITY 999999999

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int id;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

typedef struct Dijkstra {
    pnode node;
    int weight;
    int visit;
    struct Dijkstra *next;
} dijkstra, *pdijkstra;


node* creat_graph(int num_of_nodes);

void add_adge(pnode *head,int src);

void insert_edge(pnode temp,int dest,int w,pnode *head);

pnode getNode(int id, pnode *head);

void freeGraph(pnode *head);

void print_graph(pnode head);

void del_node(pnode *head);

void free_edges(pnode p);

void add_node(pnode *head);

void del_edge(pnode *head,int n);

int shortest_Path(pnode head,int src,int dest);

int TSP(pnode head);
int isEmpty(pnode p);
pnode GetNode(int id);
 

#endif