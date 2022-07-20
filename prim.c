#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include "utils.h"
#include "prim.h"



//Free Adjacency Matrix Memory
void freeTwoDArray(int** array,int numVertices){
  int i;
  for (i = 0; i < numVertices; i++){
    int* currentIntPtr = array[i];
    free(currentIntPtr);
  }
} 


// Search for vertex with minimum key value from the vertices' set (havent include in MST)
int minValKey(int keyVal[], int numVertices, bool mstSet[])
{
    int i;    
    // Initialize minimum value with infinity
    int minVal = INT_MAX, minVal_index;
  
    for (i = 0; i < numVertices; i++){
        if (keyVal[i] < minVal && mstSet[i] == false )
            minVal = keyVal[i], minVal_index = i;
    }
    return minVal_index;
}

  
//Construct MST and Return the minimum cost of the MST
int primMSTCost(int** graph,int numVertices){
    int i,j,v;

    // Store the Key values for choosing the minimum weight edge 
    int keyVal[numVertices];
    // To store the set of vertices included in MST
    bool mstSet[numVertices];
  
    // Initialize all keys with infinity
    for (i = 0; i < numVertices; i++){
        keyVal[i] = INT_MAX, mstSet[i] = false;
  
    // Include 1st vertex in MST 
    // Let key become 0 so that this vertex is picked as first vertex.
    keyVal[0] = 0;
    
    }

    // The MST will have numVertices of vertices
    for (j = 0; j < numVertices; j++) {

        // Pick the minimum key vertex from the set of vertices which not yet included in MST
        int w = minValKey(keyVal, numVertices,mstSet);
  
        // Add the chosen vertex with minimum value to the MST Set
        mstSet[w] = true;
  
        /* Update key value and parent index of the adjacent vertices of the choosen vertex.
           Only include those that not in MST  */
        for (v = 0; v < numVertices; v++){
  
            /* 1. graph[k][v] is non-zero only for adjacent vertices of mstSet[v]
               2. mstSet[v] will be false for those not included in MST's vertices
               3. Update the key when graph[k][v] is smaller than key[v] */
            if (graph[w][v] && mstSet[v] == false && graph[w][v] < keyVal[v]){
                keyVal[v] = graph[w][v];
            }
        }
    }
  

    //Calculate the total minimum cost of the MST 
    int totalMinCost = 0;

    for(i=1;i<numVertices;i++){
        
      totalMinCost += (keyVal[i]);
    }

    //printf("The minimum cost is %d\n",totalMinCost);

    //Free the Adjacency Matrix Graph
    freeTwoDArray(graph,numVertices);

    return totalMinCost;
    
}

//-----------------------------------------------------END---------------------------------------------------------------

/*
Print the MST
void printMST(int parent[], int** graph, int numVertices)
{
    printf("Edge \tWeight\n");
    for (int i = 1; i < numVertices; i++){
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
}
*/
