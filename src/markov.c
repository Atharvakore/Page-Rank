#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "store_graph.h"
#include "stats.h"
#include "argparser.h"
#include "string.h"



void markov(char *name , int n ,double p){
     double pp = (double)p/100.0;
     int nn = n;
     graph_t *g= parse_graph (name);
    
      if(g->count==0){
     //  printf("%s:\n",g->name); 
      free(g->name);
      free(g->nodes);
      free(g);
      g=NULL;
      return;
      }

      //to Store the Pi matrix
      double *pi = calloc((g->count),sizeof(double));
     // double *pi =(double*) malloc((g->count)*sizeof(double));
      if(pi==NULL){
       printf("Allocation Falied\n");
       }
      double countt = (float) g->count;
      for (int i = 0 ; i<g->count ; i++){
       pi[i]=1.0/countt;
      }
     if(nn==0){
      for (int i = 0 ; i<g->count ; i++){
      printf("%s %.10f\n", g->nodes[i]->name,pi[i]);
      free_graph(g);
      free(pi);
      }
     }
      //Adjaecent Matrix
       int adjMatrix [g->count][g->count];
       //intialization
        for (int i = 0; i < g->count; i++) {
         for (int j = 0; j < g->count; j++) {
            adjMatrix[i][j] = 0;
         }
        }
        //Filling of Adjmatrix
        for (int i = 0; i < g->count; i++) {
        node_t *node = g->nodes[i];
         for (int j = 0; j < node->num_edges; j++) {
            node_t *rd = node->out_edges[j];
             for (int k = 0; k < g->count ; k++) {
                 if (g->nodes[k] == rd) {
                    adjMatrix[i][k]++;  
                    break;
                 }
             }
        }
      }
  
     
 
      // pp=0.1500;
      //Matrix for Multiplication
      
       double matrix[g->count][g->count]; 
       for(int i = 0 ; i <g->count ; i++ ){       
       for(int j = 0 ; j <g->count ; j++){
            if(g->nodes[i]->num_edges==0){
              matrix[i][j]=1.0/(double)g->count;
            }else{
                matrix[i][j]=((pp/(double)g->count)+(((1-pp)*(adjMatrix[i][j]))/(g->nodes[i]->num_edges)));
                 //matrix[i][j]=pp*(1.0/g->count)+(1-pp)*((double)adjMatrix[i][j]/g->nodes[i]->num_edges);
            }
         
        }
       }
 
       
  //Matrix Multipliacation
  double system [g->count] ;
 /* for(int s = 0 ; s<g->count ; s++){
   system[s]=0.0;
  }*/
  for(int k = 0 ; k < nn ; k++){
    memset(system,0,sizeof(double)*g->count);
   for (int j = 0; j < g->count; j++) {
        for (int i = 0; i < g->count; i++) {
            system[j] +=   matrix[i][j] * pi[i];
        }
    }
    
   // for(int r = 0 ; r<g->count ; r++){
     //pi[r]=system[r];
     //system[r]=0;
    //}
    memcpy(pi,system,sizeof(double)*g->count);
  } 
  for(int y = 0 ; y < g->count ;y++){
    printf("%s %.10f\n", g->nodes[y]->name,pi[y]);
  }
      free_graph(g);
      free(pi);
}
