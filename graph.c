/*
graph.c

Set of vertices and edges implementation.

Implementations for helper functions for graph construction and manipulation.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021
*/
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include "graph.h"
#include "utils.h"
#include "pq.h" 
#include "prim.h"

#define INITIALEDGES 32
#define CABLED 0

struct edge;

/* Definition of a graph. */
struct graph {
  int numVertices;
  int numEdges;
  int allocedEdges;
  struct edge **edgeList;
};


/* Definition of an edge. */
struct edge {
  int start;
  int end;
  int cost;
};


struct graph *newGraph(int numVertices){
  struct graph *g = (struct graph *) malloc(sizeof(struct graph));
  assert(g);
  /* Initialise edges. */
  g->numVertices = numVertices;
  g->numEdges = 0;
  g->allocedEdges = 0;
  g->edgeList = NULL;
  return g;
  
}


/* Adds an edge to the given graph. */
void addEdge(struct graph *g, int start, int end, int cost){
  assert(g);
  struct edge *newEdge = NULL;
  /* Check we have enough space for the new edge. */
  if((g->numEdges + 1) > g->allocedEdges){
    if(g->allocedEdges == 0){
      g->allocedEdges = INITIALEDGES;
    } else {
      (g->allocedEdges) *= 2;
    }
    g->edgeList = (struct edge **) realloc(g->edgeList,
      sizeof(struct edge *) * g->allocedEdges);
    assert(g->edgeList);
  }

  /* Create the edge */
  newEdge = (struct edge *) malloc(sizeof(struct edge));
  assert(newEdge);
  newEdge->start = start;
  newEdge->end = end;
  newEdge->cost = cost;

  /* Add the edge to the list of edges. */
  g->edgeList[g->numEdges] = newEdge;
  (g->numEdges)++;
  
}


/* Frees all memory used by graph. */
void freeGraph(struct graph *g){
  int i;
  for(i = 0; i < g->numEdges; i++){
    free((g->edgeList)[i]);
  }
  if(g->edgeList){
    free(g->edgeList);
  }
  free(g);
}


struct solution *graphSolve(struct graph *g, enum problemPart part,
  int antennaCost, int numHouses){
  struct solution *solution = (struct solution *)
    malloc(sizeof(struct solution));
  assert(solution);
  int** adjMatrix;

  if(part == PART_A){
    /* IMPLEMENT 2A SOLUTION HERE */
   
    //Cost of Radio-based installation
    solution->antennaTotal = numHouses * antennaCost;

    //Cost of Cabled installation

    //Convert List to Adjacency Matrix
    adjMatrix = convertToAdjMatrix(g);

    //Initialize Adjacency Matrix with Specified Value
    inputAdjMatrix(g,adjMatrix,CABLED);
    
    //Process minimum edge because got different cost on same edge
    //When There are different cost on same edge, choose the smallest
    lowestEdgeCost(g,adjMatrix);
    //printAdjMatrix(g,adjMatrix);

    solution->cableTotal = primMSTCost(adjMatrix,g->numVertices);


  } else {

    /* IMPLEMENT 2C SOLUTION HERE */

    //Convert List to Adjacency Matrix
    adjMatrix = convertToAdjMatrix(g);

    //Initialize Adjacency Matrix with Specified Value
    inputAdjMatrix(g,adjMatrix,antennaCost);
    
    //Process minimum edge because got different cost on same edge
    //When There are different cost on same edge, choose the smallest
    lowestEdgeCost(g,adjMatrix);

    //printAdjMatrix(g,adjMatrix);

    //Solution for the Mixed Total Cost
    solution->mixedTotal = primMSTCost(adjMatrix,g->numVertices);

  }
  return solution;
}




//Convert List to Adjacency Matrix
int** convertToAdjMatrix(struct graph *g){

  int i;

  // Declare Memory Allocation for Adjacency Matrix
  int** adj_matrix;

  adj_matrix = (int**) malloc (sizeof(int **)*(g->numVertices));
  assert(adj_matrix);
  
  
  for (i=0;i<g->numVertices;i++){
    adj_matrix[i] = (int*) malloc (sizeof(int)*(g->numVertices));
    assert(adj_matrix[i]);
  }

  return adj_matrix;
    
}




//Initialize Adjacency Matrix with Specified Cost
void inputAdjMatrix(struct graph *g,int** adj_matrix,int cost){  
  int i,j;
  for (i=0; i<(g->numVertices);i++ ){
    for (j = 0; j<(g->numVertices);j++){
      adj_matrix[i][j] = cost;
    }
  }
}




//Choose the minimum edge because got different cost on same edge
void lowestEdgeCost(struct graph *g,int** adj_matrix){
  int i;
  //Input vertices into matrix
  for (i=0;i < (g->numEdges);i++){

    // Allocate initial cost for the matrix
    adj_matrix[g->edgeList[i]->start][g->edgeList[i]->end] = (g->edgeList[i]->cost);
  }

  //When There are different cost on same edge, choose the smallest cost
  for (i=0;i < (g->numEdges);i++){

    //When [start][end] smaller than [end][start],[end][start] equal to the initial allocated cost
    if((adj_matrix[g->edgeList[i]->start][g->edgeList[i]->end]< adj_matrix[g->edgeList[i]->end][g->edgeList[i]->start])){

      adj_matrix[g->edgeList[i]->end][g->edgeList[i]->start] = adj_matrix[g->edgeList[i]->start][g->edgeList[i]->end];
      //When [end][start] smaller than [start][end],[end][start] equal to the initial allocated cost
    }else{

      adj_matrix[g->edgeList[i]->end][g->edgeList[i]->start] = adj_matrix[g->edgeList[i]->start][g->edgeList[i]->end];
    }   
  }
 for (i=0;i < (g->numEdges);i++){
    adj_matrix[g->edgeList[i]->end][g->edgeList[i]->start] = adj_matrix[g->edgeList[i]->start][g->edgeList[i]->end];
 }

}


//----------------------------------------------END-------------------------------------------------------------------------

/*
//Print The Adjacency Matrix
void printAdjMatrix(struct graph *g,int** adj_matrix){
  int i,j;
  // Print out the array   
  for(i=0;i<g->numVertices;i++){
    printf("\n");
    for(j=0; j<g->numVertices;j++){
      printf("%4d ",adj_matrix[i][j]);

    }
  }
  printf("\n");
}
*/


/*
  Print the Matrix
  for(int i=0;i<g->numEdges;i++){
    printf("%d %d %d\n",g->edgeList[i]->start,g->edgeList[i]->end, g->edgeList[i]->cost);
  }
  */


