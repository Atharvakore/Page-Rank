
#ifndef STORE_GRAPH_H
#define STORE_GRAPH_H
#define MY_INT_MAX 2147483647  //rethink
#define MAX_LINE_LENGTH 1024
#define MAX_IDENTIFIER_LENGTH 257
typedef struct node {
    char *name;
    unsigned num_edges;
   // unsigned touch;
    struct node **out_edges;
    unsigned in_edges;  
} node_t;
typedef struct graph {
  /* nodes in the graph */
 node_t **nodes;
 unsigned count;
 char* name;
} graph_t;
graph_t *init_graph (const char *name);
void free_graph (graph_t *graph);
node_t *get_node_from_graph(graph_t *graph, const char *name);
void add_edge_to_node(node_t *source, node_t *target);
graph_t *parse_graph(const char *filename);


#endif