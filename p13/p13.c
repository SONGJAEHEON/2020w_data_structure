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
}