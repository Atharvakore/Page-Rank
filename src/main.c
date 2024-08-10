#include "argparser.h"
#include "markov.h"
#include "store_graph.h"
#include "utils.h"
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>




int main(int argc, char *const *argv) {
  // initialize the random number generator
  // rand_init();
  arg_t arguments = parse_arguments(argc, argv);
  //printf("%d %f %s\n",arguments.rn,arguments.p,arguments.name);
  char *filename = arguments.name;
  if(arguments.s==1){
  print_stats(filename);
  }

  if(arguments.rn!=-1){
  int n =arguments.rn;
  double pp = arguments.p; 
  random_surf( filename,n,pp);
  }
  if(arguments.mn!=-1){
  int n = arguments.mn; 
  double pp = arguments.p;
  markov( filename,n,pp);
  }



  // TODO: Implement me
  exit(0);
}
void random_surf(char *name , int n , double p){
   // printf("%s %d %f\n",name,n,p);
   graph_t *g =  parse_graph(name);
   if(g->count==0){
    free(g->name);
    free(g->nodes);
     exit(0);
   }
   if (!g) {  
        fprintf(stderr, "Graph does not exist\n");
        return;
    }
    int *touch = calloc(g->count, sizeof(int));
    if (!touch) {
        fprintf(stderr, "allocation failed !\n");
        return;
    }

   rand_init();
    int initiate = randu(g->count);
    

    for (int i = 0; i < n; ++i) {
        //printf("%d\n",initiate);
        int r= randu(100);  
        if (r < p) {
  
            initiate = randu(g->count);
        } else {
            //printf("%d\n",num_edges);
            node_t *i = g->nodes[initiate];
            if (i->num_edges > 0) {
                int randomlink = randu(i->num_edges);
       
                if (randomlink >= 0 && randomlink < i->num_edges) {

                    node_t *link= i->out_edges[randomlink];
                    for (int k=0; k<g-> count; k++ ){
                        //case 1
                        if (g->nodes[k]==link){
                            initiate=k;
                            break;
                        }
                     }
                }
                //case 2
            } else {
              
                initiate = randu(g->count);
            }
        }
        touch[initiate]++;
    }



//for printing
    for (int i = 0; i < g->count; ++i) {
        double t = (double)touch[i]/n;
        
        printf("%s\t%.10f\n", g->nodes[i]->name,t);
    }
     
    free(touch);
    free_graph(g);
 }