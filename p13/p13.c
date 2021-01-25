#include <stdio.h>
#include <stdlib.h>

typedef struct Graph{
    int num;
    int ** weight;
    int * check_visit;
} graph;

typedef struct Stack{
    int * contetn;
    int top;
    int max_stack_size;
} stack;

typedef struct CircularQueue{
    int * content;
    int first;
    int rear;
    int qsize;
    int max_queue_size;
} queue;

graph makeGraph(FILE * fi);
void DFS_recursive(graph g, int start, int end);
void DFS_iterative(graph g, int start, int end);
void BFS_search(graph g, int start, int end);
stack * create_stack(int num);
void push(stack * s, int value);
int pop(stack * s);
void close_stack(stack * s);
queue * create_queue(int size);
void enqueue(queue * q, int value);
int dequeue(queue * q);
void close_queue(queue * q);

void main(int argc, char* argv[]){
    FILE * fi = fopen(argv[1], "r");
    graph g = makeGraph(fi);

    int start, end;
    fscanf(fi, "%d-%d", &start, &end);

    printf("DFS recursive : ");
    DFS_recursive(g, start, end);
    if(g.num < end)
        printf("cannot find");
    else if(g.check_visit[end-1] == 0)
        printf("cannot find");

    printf("\nDFS iterative : ");
    DFS_iterative(g, start, end);

    printf("\nBFS : ");
    BFS_search(g, start, end);
    printf("\n");

    //free the memory and close file
    fclose(fi);
}

graph makeGraph(FILE * fi){
    int i, m, n;
    char buf[100];
    graph * g = (graph *)malloc(sizeof(graph));
    fscanf(fi, "%d", &i);
    g->num = i;
    *g->weight = (int *)malloc(sizeof(int)*(i+1));
    g->weight = (int **)malloc(sizeof(int)*(i+1));
    g->check_visit = (int *)malloc(sizeof(int)*(i+1));
    fgets(buf, sizeof(buf), fi);
    while(!feof(buf)){
        fscanf(buf, "%d-%d", &m, &n);
        g->weight[m][n] = 1;
    }
    fscanf(fi, "%d-%d", &m, &n);

    for(int j = 1; j <= i; j++){
        for(int k = 1; k <= j; k++){
            printf("%d ", g->weight[j][k]);
        }
        printf("\n");
    }
    printf("%d-%d", m, n);

    return * g;
}
