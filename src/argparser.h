// argparser.h

#ifndef ARG_PARSER_H
#define ARG_PARSER_H

typedef struct {
    char *name; 
    int rn; 
    int mn; 
    int s; 
    double p; 
} arg_t;


arg_t parse_arguments(int argc, char *argv[]);


void print_usage(const char *prog_name);

#endif 
