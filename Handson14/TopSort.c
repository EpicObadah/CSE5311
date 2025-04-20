#include <stdio.h>
#include <stdlib.h>

#define MAX_VERT 100

typedef struct Node
{
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph
{
    int vertCount;
    Node* adjList[MAX_VERT];
    int visited[MAX_VERT];
} Graph;

int stack[MAX_VERT];
int top = -1;

Node* createNode(int v);
//Graph* createGraph(int vertices);
void addEdge(Graph* graph, int from, int to);
void push(int vertex);
void topologicalSortU(Graph* graph, int v);
void topologicalSort(Graph* graph);


int main()
{
    int vert = 6;
    //Graph* graph = createGraph(vert);

    Graph* graph = malloc(sizeof(Graph));
    graph->vertCount = vert;

    for(int i = 0; i < vert; i++)
    {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    topologicalSort(graph);

    return 0;
}

Node* createNode(int v)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

/*
Graph* createGraph(int vertices)
{
    Graph* graph = malloc(sizeof(Graph));
    graph->vertCount = vertices;

    for(int i = 0; i < vertices; i++)
    {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}
*/
void addEdge(Graph* graph, int from, int to)
{
    Node* newNode = createNode(to);
    newNode->next = graph->adjList[from];
    graph->adjList[from] = newNode;
}

void push(int vertex)
{
    stack[++top] = vertex;
}

void topologicalSortU(Graph* graph, int v)
{
    graph->visited[v] = 1;

    Node* temp = graph->adjList[v];
    while (temp != NULL)
    {
        int adjVertex = temp->vertex;
        if(!graph->visited[adjVertex])
        {
            topologicalSortU(graph, adjVertex);
        }
        temp = temp->next;
    }
    push(v);
    
}

void topologicalSort(Graph* graph)
{
    for (int i = 0; i < graph->vertCount; i++)
    {
        if(!graph->visited[i])
        {
            topologicalSortU(graph, i);
        }
    }

    printf("Topological Sort: \n");
    while (top != -1)
    {
        printf("%d ", stack[top--]);
    }

    printf("\n");
}