#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "store_graph.h"



graph_t *init_graph(const char *name) {
    graph_t *graph = calloc(1, sizeof(graph_t));
    if (!graph) {
        fprintf(stderr, "Allocation failed! %s\n", name);
        exit(1);
    }
    graph->nodes = NULL;
    graph->count = 0;
    graph->name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(graph->name, name);
    return graph;
}

void free_graph(graph_t *graph) {
    for (unsigned i = 0; i < graph->count; i++) {
        node_t *node = graph->nodes[i];
        free(node->out_edges);
        free(node->name);
        free(node);
    }
    free(graph->name);
    free(graph->nodes);
    free(graph);
}

node_t *get_node_from_graph(graph_t *graph, const char *name) {
    for (unsigned i = 0; i < graph->count; i++) {
        node_t *node = graph->nodes[i];
        if (!strcmp(node->name, name)) {
            return node;
        }
    }
    node_t *node = calloc(1, sizeof(node_t));
    node->out_edges = NULL;
    node->num_edges = 0;
    node->in_edges = 0;  
    //node->touch = 0;
    node->name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(node->name, name);
    graph->nodes = realloc(graph->nodes, (graph->count + 1) * sizeof(node_t*));
    graph->nodes[graph->count++] = node;
    return node;
}

void add_edge_to_node(node_t *s, node_t *t) {
    s->out_edges = realloc(s->out_edges, (s->num_edges + 1) * sizeof(node_t*));
    s->out_edges[s->num_edges++] = t;
    t->in_edges++;
}

graph_t *parse_graph(const char *filename) {
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Given filename matches no file!\n");
        exit(1);
    }

    char s_name[MAX_IDENTIFIER_LENGTH];
    if (fscanf(file, " digraph %s {", s_name) != 1) {
        fprintf(stderr, "Failed to read graph name!\n");
        fclose(file);
        exit(1);
    }

    graph_t *graph = init_graph(s_name);
    while (fgets(line, sizeof(line), file)) {
        char s_name[MAX_IDENTIFIER_LENGTH] = {0};
        char t_name[MAX_IDENTIFIER_LENGTH] = {0};

        if (sscanf(line, " %[^-> ] -> %[^; ];", s_name, t_name) == 2) {
            char *end;

            end = s_name + strlen(s_name) - 1;
            while (end > s_name && *end == ' ') end--;
            *(end + 1) = '\0';

            end = t_name + strlen(t_name) - 1;
            while (end > t_name && *end == ' ') end--;
            *(end + 1) = '\0';

            if (s_name[0] == '}' || t_name[0] == '}') break;

            node_t *s_node = get_node_from_graph(graph, s_name);
            node_t *t_node = get_node_from_graph(graph, t_name);
            add_edge_to_node(s_node, t_node);
        }
    }

    fclose(file);

    if (line[0] != '}' || strstr(line, "}") == NULL) {
        fprintf(stderr, " missing closing brace\n");
        free_graph(graph);
        exit(1);
    }

    return graph;
}
