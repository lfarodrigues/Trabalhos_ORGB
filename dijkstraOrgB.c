#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define V 1000
int** graph = NULL;

int minDistance(int dist[], bool sptSet[]){
    int min= INT_MAX, min_index;

    for(int v=0; v < V; v++)
        if(sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index= v;

        return min_index;
}

void printSolution(int dist[]){
    printf("Vertex \t\t Distance from Source \n");
    for(int i = 0; i < V; i++)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}

void dijkstra(int src){
    int dist[V];
    bool sptSet[V];

    for(int i =0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    dist[src] = 0;
    for(int count = 0; count < V - 1; count++){
        int u= minDistance(dist, sptSet);
        sptSet[u] = true;
        for(int v = 0; v < V; v++)
            if(!sptSet[v] && graph[u][v]
            && dist[u] != INT_MAX
            && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph [u][v];
    }
    printSolution(dist);
}
int main() {
    graph = (int**)malloc(V * sizeof (int *));
    for(int i = 0; i < V; i++){
        graph[i] = (int *)malloc(V * sizeof (int));
        for(int j = 0; j < V; j++){
            graph[i][j] = abs(j -i) * abs(j - i) + j - i;
        }
    }
    dijkstra(0);
    return 0;
}
