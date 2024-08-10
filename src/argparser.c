// argparser.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "argparser.h"

// to print usage information
void print_usage(const char *vishay) {
    printf("Usage: %s [OPTIONS] ... [FILENAME]\n", vishay);
    printf("Perform pagerank computations for a given file in the DOT format\n");
    printf("  -h     Print a brief overview of the available command line parameters\n");
    printf("  -r N   Simulate N steps of the random surfer and output the result\n");
    printf("  -m N   Simulate N steps of the Markov chain and output the result\n");
    printf("  -s     Compute and print the statistics of the graph as defined in section 3.4\n");
    printf("  -p P   Set the parameter p to P%%. (Default: P = 10)\n");
}


    arg_t parse_arguments(int argc, char *argv[]) {
    arg_t args;
    args.name = NULL;
    args.rn = -1;
    args.mn = -1;
    args.s = 0;
    args.p = 10; // Default value

    int opt;
    while ((opt = getopt(argc, argv, "hr:m:sp:")) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                exit(EXIT_SUCCESS);
            case 'r':
                args.rn = atoi(optarg);
                if(args.rn<=0){
                 exit(1);
                }
              //  args.p = atoi(optarg); //I am not able to do it now !
                break;
            case 'm':
                args.mn = atoi(optarg);
               
                if(args.mn<=0){
                 exit(1);
                }
                break;
            case 's':
                args.s = 1;
                break;
            case 'p':
                args.p = atoi(optarg);
                if(args.p<=0||args.p>100){
                 exit(0);
                }
                break;
            default:
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        args.name = argv[optind];
    } else {
        fprintf(stderr, "Error: Input filename is required.\n");
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    return args;
}
