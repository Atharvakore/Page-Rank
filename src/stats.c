#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "store_graph.h"

void print_stats(char *c){
    graph_t *g= parse_graph (c);
    if(g->count==0){
     printf("%s:\n",g->name);  
     printf("- num nodes: %d\n",0);
     printf("- num edges: %d\n",0);
     printf("- indegree: 0-0\n");
     printf("- outdegree: 0-0\n");
    free(g->name);
    free(g);
    return;
    }
   printf("%s:\n",g->name);
   printf("- num nodes: %d\n",g->count);
    int size = 0;
   for(int i=0 ; i<g->count ; i++){
    node_t *t = g->nodes[i];
     size = size + (t->num_edges);
  
   }
   printf("- num edges: %d\n",size); 
   //for out_edges and In_Edges
   int max_out=0;
   int min_out= MY_INT_MAX;
   int max_in=0;
   int min_in= MY_INT_MAX;
   
    for(int i=0 ; i<g->count ; i++){
    node_t *t = g->nodes[i];
    if((t->num_edges)>max_out){
    max_out=(t->num_edges);
    }
    if((t->num_edges)<min_out){
    min_out=(t->num_edges);
    
    }
    if(t->in_edges>max_in){
    max_in=(t->in_edges);
    }
    if(t->in_edges<min_in){
    min_in=(t->in_edges);
    }
    
   }
   printf("- indegree: %d-%d\n",min_in,max_in);
   printf("- outdegree: %d-%d\n",min_out,max_out);

 free_graph(g);
 return;
}