#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "mylib.h"
#include "getopt.h"

typedef enum { UNVISTED, VISTED_SELF,VISTED_DESCENDANTS } state_t;

struct vertexrec{
    int predeccessor;
    int distance;
    int finish;
    state_t state;
};

struct graphrec{
    int capacity;
    int **edges;
    struct vertexrec *vertices;
};

graph graph_new(int num_vertices) {
    int i;
    graph g = emalloc(sizeof *g);
    g -> capacity = num_vertices;
    g -> edges = emalloc(g -> capacity *sizeof g -> edges[0]);
    g -> vertices = emalloc(g -> capacity *sizeof g -> vertices[0]);
    for (i = 0; i < g -> capacity; i++)
    {
        g -> edges[i] = emalloc(g -> capacity *sizeof g -> vertices[i]);
    }
    return g;
}
/*Function for adding a edge*/
void graph_add_edge(graph g, int u , int v){
    g->edges[u][v] = 1;

}
/*Function for adding bidirectional edges*/
void graph_add_2edges(graph g, int u, int v){
    g->edges[u][v] =1;
    g->edges[v][u] =1;
}
/*Free function for graph*/
graph graph_free(graph g){
    int i;
    for(i=0; i < g->capacity; i++){
        free(g->edges[i]);
    }
    free(g->edges);
    free(g->vertices);
    free(g);
    return g;
}
/*Print function for matrix*/
void graph_print_state(graph g){
    int i;
    printf("vertex distance pred finish\n");
    for (i = 0; i < g->capacity; i++){
        printf("%5d %6d %5d %5d\n", i, g->vertices[i].distance,
               g->vertices[i].predeccessor, g->vertices[i].finish);
    }
}
/*Prints function for adjacency list and graph table*/
void graph_print_list(graph g){
   int i;
   int j = 0;
   int count = 0;
   printf("adjacency list:\n");
   for (i = 0; i < g->capacity; i++) {
       printf("%d |", i);
       count = 0;
       for (j = 0; j < g->capacity; j++) {
           if (g->edges[i][j] == 1) {
               if (count == 0) {
                   printf(" %d", j);
                   count++;
               }else {
                   printf(", %d", j);
               }
           }
       }
       printf("\n");
   }
}

/*Graph Depth first Search implementation */
 int step;

graph graph_dfs(graph g){
    int i;
    for(i =0; i< g->capacity; i++){
        g->vertices[i].state = UNVISTED;
        g->vertices[i].predeccessor = -1;
    }

    step =0;
    for(i=0; i< g->capacity; i++){
        if(g->vertices[i].state == UNVISTED){
            visit(g,i);
        }
    }
    graph_print_state(g);
    return g;
}

void visit(graph g ,int v){
    int u;
    g->vertices[v].state=VISTED_SELF;
    step++;
    g->vertices[v].distance = step;

    for(u=0; u < g->capacity; u++){
        if(g->edges[v][u] ==1 && g->vertices[u].state ==UNVISTED){
            g->vertices[u].predeccessor=v;
            visit(g,u);
        }
    }
    step++;
    g->vertices[v].state=VISTED_DESCENDANTS;
    g->vertices[v].finish=step;
}
