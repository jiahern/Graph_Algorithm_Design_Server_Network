/*prim.h

PRIM Algorithm Implmentation and Represent the minimum cost.

Created by Jia Hern Lee 997562


*/

// Because have bool type in the function declaration
#include <stdbool.h>



//Free the Adjacency Matrix Memory
void freeTwoDArray(int** ptr,int numVertices);


// Search for vertex with minimum key value from the vertices' set (havent include in MST)
int minValKey(int keyVal[], int numVertices, bool mstSet[]);


// Construct MST and Return the minimum cost of the MST
int primMSTCost(int** graph, int numVertices);


