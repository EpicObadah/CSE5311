#include <stdio.h>

#define VERTCOUNT 4
#define INF 999999999  // Representation of infinite distance

void floydWarshall(int graph[VERTCOUNT][VERTCOUNT]);


int main() 
{
    int graph[VERTCOUNT][VERTCOUNT] = {
        {0,   5,  INF, 10},
        {INF, 0,   3,  INF},
        {INF, INF, 0,   1},
        {INF, INF, INF, 0}
    };

    floydWarshall(graph);

    return 0;
}




void floydWarshall(int graph[VERTCOUNT][VERTCOUNT]) 
{
    int dist[VERTCOUNT][VERTCOUNT];

    for (int i = 0; i < VERTCOUNT; i++)
    {
        for (int j = 0; j < VERTCOUNT; j++)
        {
            dist[i][j] = graph[i][j];
        }
    }


    for (int k = 0; k < VERTCOUNT; k++) 
    {
        for (int i = 0; i < VERTCOUNT; i++) 
        {
            for (int j = 0; j < VERTCOUNT; j++) 
            {
                // If vertex k is on the shortest path from i to j, then update dist[i][j]
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Check for negative cycles
    for (int i = 0; i < VERTCOUNT; i++) 
    {
        if (dist[i][i] < 0) 
        {
            printf("Graph has negative-weight cycle\n");
            return;
        }
    }

    printf("Shortest distances between each pair of vertices:\n");
    for (int i = 0; i < VERTCOUNT; i++) 
    {
        for (int j = 0; j < VERTCOUNT; j++) 
        {
            if (dist[i][j] == INF)
            {
                printf("%7s", "INF");
            }
            else
            {
                printf("%7d", dist[i][j]);
            }
        }
        printf("\n");
    }
}