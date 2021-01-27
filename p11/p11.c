#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Graph * Graph;
typedef struct _Queue * Queue;

struct _Graph{
    int size;
    int * node;
    int ** matrix;
};

struct _Queue{
    int * key;
    int first;
    int rear;
    int qsize;
    int max_queue_size;
};

Graph CreateGraph(int * nodes);
void InsertEdge(Graph G, int a, int b);
void DeleteGraph(Graph G);
void Topsort(Graph G);
Queue MakeNewQueue(int X);
int IsEmpty(Queue Q);
int IsFull(Queue Q);
int DeQueue(Queue Q);
void EnQueue(Queue Q, int X);
void DeleteQueue(Queue Q);
void MakeEmpty(Queue Q);

int main(int argc, char ** argv){
    Graph g;
    char temp;
    int arr[100] = {0,};
    int i = 0, from, to;
    FILE * fi = fopen(argv[1], "r");
    while(temp != '\n'){
        fscanf(fi, "%c", &temp);
        arr[i++] = (int)temp - 48;
        temp = fgetc(fi);
    }
    g = CreateGraph(arr);
    do{
        fscanf(fi, "%d-%d", &from, &to);
        InsertEdge(g , from, to);
        temp = fgetc(fi);
    }while(!feof(fi));
    Topsort(g);
    DeleteGraph(g);
    fclose(fi);

    return 0;
}

Graph CreateGraph(int * nodes){
    Graph g;
    g = (Graph)malloc(sizeof(Graph));
    int cnt = 0, t = 0, max = 0;
    int * nodearr;
    while(nodes[t] != 0){
        if(nodes[t] > max) max = nodes[t];
        t++;
    }
    nodearr = (int *)malloc(sizeof(int)*(max+1));
    for(t = 0; t <= max; t++){
        nodearr[t] = 0;
    }
    for(t = 0; t <= max; t++){
        nodearr[nodes[t]] = 1;
    }
    int ** matrixarr = (int **)malloc(sizeof(int *)*(max+1));
    for(int i = 0; i <= max; i++){
        matrixarr[i] = (int *)malloc(sizeof(int)*(max+1));
    }
    g->size = max;
    g->node = nodearr;
    g->matrix = matrixarr;

    return g;
}

void InsertEdge(Graph G, int a, int b){
    G->matrix[a][b] = 1;

    return;
}

void DeleteGraph(Graph G){
    free(G->node);
    free(G->matrix);
    free(G);

    return;
}

void Topsort(Graph G){
    Queue q = MakeNewQueue(G->size);
    int count = 0, dq;
    int * arr = (int *)malloc(sizeof(int)*(G->size+1));
    int * visited = (int *)malloc(sizeof(int)*(G->size+1));
    for(int i = 0; i <= G->size; i++){
        arr[i] = 0;
        visited[i] = 0;
    }
    for(int i = 1; i <= G->size; i++){
        if(G->node[i] == 0){
            visited[i] = 1;
            count++;
            continue;
        }
        else{
            int cnt = 0;
            for(int j = 1; j <= G->size; j++){
                if(G->matrix[j][i] == 1) cnt++;
            }
            arr[i] = cnt;
        }
    }
    while(count < G->size){
        for(int i = 1; i <= G->size; i++){
            if(arr[i] == 0 && !visited[i]){
                EnQueue(q, i);
                visited[i] = 1;
            }
        }
        //do{
        dq = DeQueue(q);
        printf("%d ", dq);
        count++;
        for(int j = 1; j <= G->size; j++){
            if(G->matrix[dq][j] == 1){
                G->matrix[dq][j] = 0;
                arr[j]--;
            }
        }
        putchar('\n');
        //}while(!IsEmpty(q));
    }
    DeleteQueue(q);
    free(arr);
    free(visited);

    return;
}

Queue MakeNewQueue(int X){
    Queue q = (Queue)malloc(sizeof(Queue));
    q->key = (int *)malloc(sizeof(int)*X);
    for(int i = 0; i < X; i++){
        q->key[i] = 1000;
    }
    q->first = q->rear = q->qsize = 0;
    q->max_queue_size = X;

    return q;
}

int IsEmpty(Queue Q){
    return Q->qsize == 0;
}

int IsFull(Queue Q){
    return Q->qsize == Q->max_queue_size;
}

int DeQueue(Queue Q){
    Q->first = ++Q->first%Q->max_queue_size;
    int rtn = Q->key[Q->first];
    Q->key[Q->first] = 1000; 
    Q->qsize--;
    return rtn;
}

void EnQueue(Queue Q, int X){
    if(IsFull(Q)){
        printf("Queue is full \n");
        return;
    }
    int tmp, front;
    front = (Q->first+1)%Q->max_queue_size;
    Q->rear = ++Q->rear%Q->max_queue_size;
    while(X > Q->key[front]) front++;
    while(front != Q->rear){
        tmp = Q->key[front];
        Q->key[front] = X;
        X = tmp;
        front = (++front)%Q->max_queue_size;
    }
    Q->key[front] = X;
    Q->qsize++;

    return;
}

void DeleteQueue(Queue Q){
    free(Q->key);
    free(Q);

    return;
}

void MakeEmpty(Queue Q){
    for(int i = 0; i < Q->max_queue_size; i++){
        Q->key[i] = 0;
    }
    Q->first = Q->rear = Q->qsize = Q->max_queue_size = 0;

    return;
}