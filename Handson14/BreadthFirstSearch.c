// Professor said to do Breadthfirstsearch in the lecture, but he did not update the handson to say this.

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

typedef struct Queue
{
    int items[MAX_VERT];
    int front;
    int rear;
} Queue;

Node* createNode(int v);
void addEdge(Graph* graph, int from, int to);
Queue* createQueue();
int isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
void bfs(Graph* graph, int startVertex);

int main()
{
    int vert = 6;
    Graph* graph = malloc(sizeof(Graph));
    graph->vertCount = vert;

    for (int i = 0; i < vert; i++) 
    {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    bfs(graph, 0);

    return 0;
}

Node* createNode(int v) 
{
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph* graph, int from, int to) 
{
    Node* newNode = createNode(to);
    if(graph->adjList[from] == NULL)
    {
        graph->adjList[from] = newNode;
    }
    else
    {
        Node* temp = graph->adjList[from];
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
}

Queue* createQueue()
{
    Queue* q = malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(Queue* q)
{
    return q->rear == -1;
}

void enqueue(Queue* q, int value)
{
    if (q->rear == MAX_VERT -1)
    {
        return;
    }

    if(isEmpty(q))
    {
        q->front = 0;
    }

    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q)
{
    if (isEmpty(q))
    {
        return -1;
    }

    int item = q->items[q->front];
    q->front++;

    if(q->front > q->rear)
    {
        q->front = q->rear = -1;
    }

    return item;
}

void bfs(Graph* graph, int startVertex)
{
    Queue* q = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    printf("BFS traversal:\n");
    while(!isEmpty(q))
    {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);

        Node* tmp = graph->adjList[currentVertex];

        while(tmp != NULL)
        {
            int adjVertex = tmp->vertex;

            if(!graph->visited[adjVertex])
            {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }

            tmp = tmp->next;
        }
    }

    printf("\n");
}
