#include <stdio.h>
#include <stdlib.h>

typedef struct Graph{
    int num;
    int ** weight;
    int * check_visit;
} graph;

typedef struct Stack{
    int * content;
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
void DFS_recur(graph * g, int k, int end);
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
    else if(g.check_visit[end] == 0)
        printf("cannot find");

    printf("\nDFS iterative : ");
    DFS_iterative(g, start, end);


    printf("\nBFS : ");
    BFS_search(g, start, end);
    printf("\n");

    fclose(fi);

    return;
}

graph makeGraph(FILE * fi){
    char ch;
    int from, to;
    ch = fgetc(fi);
    graph * g = (graph *)malloc(sizeof(graph));
    g->num = (int)ch-48;
    int * arr1 = (int *)malloc(sizeof(int)*g->num);
    for(int i = 0; i <= g->num; i++){
        arr1[i] = 0;
    }
    int ** arr2 = (int **)malloc(sizeof(int *)*(g->num+1));
    for(int i = 0; i <= g->num; i++){
        arr2[i] = (int*)malloc(sizeof(int)*(g->num+1));
    }
    for(int i = 0; i <= g->num; i++){
        for(int j = 0; j <= g->num; j++){
            arr2[i][j] = 0;
        }
    }
    g->check_visit = arr1;
    g->weight = arr2;
    ch = fgetc(fi);
    do{
        fscanf(fi, "%d-%d", &from, &to);
        g->weight[from][to] = 1;
        ch = fgetc(fi);
    } while(ch != '\n');

    return * g;
}

void DFS_recursive(graph g, int start, int end){
    int  i = start, j = 0;
    for(int m = 1; m <= g.num; m++){
        if(g.weight[i][m] == 1){
            j = m;
            break;
        }
    }
    if(j == 0){
        printf("cannot find the starting numebr!\n");
        return;
    }
    DFS_recur(&g, i, end);

    return;
}

void DFS_recur(graph * g, int k, int end){
    if(g->check_visit[k] == 1 || g->check_visit[end] == 1) return;
    g->check_visit[k] = 1;
    printf("%d ", k);
    if(k == end) return;
    for(int i = 1; i <= g->num; i++){
        if(g->weight[k][i] == 1){
            DFS_recur(g, i, end);
        }
    }

    return;
}

void DFS_iterative(graph g, int start, int end){
    int i = start, j= 0, cnt = 0;
    stack * s = create_stack(g.num);

    for(int l = 1; l <= g.num; l++){
        g.check_visit[l] = 0;
    }

    for(int m = 1; m <= g.num; m++){
        if(g.weight[i][m] == 1){
            j = m;
            break;
        }
    }
    if(j == 0){
        printf("cannot find the starting number!\n");
        return;
    }
    g.check_visit[i] = 1;
    cnt++;
    printf("%d ", i);
    while(cnt < g.num){
        if(i == end) break;
        for(j = 1; j <= g.num; j++){
            if(g.weight[i][j] == 1){
                if(g.check_visit[j] == 1) continue;
                else{
                    g.check_visit[j] = 1;
                    push(s, j);
                }
            }
        }
        i = pop(s);
        printf("%d ", i);
        cnt++;
    }
    if(g.num < end)
        printf("cannot find");
    else if(g.check_visit[end] == 0)
        printf("cannot find");
    close_stack(s);

    return;
}

void BFS_search(graph g, int start, int end){
    int i = start, j, cnt = 0;
    queue * q = create_queue(g.num);

    for(int l = 1; l <= g.num; l++){
        g.check_visit[l] = 0;
    }

    for(int m = 1; m <= g.num; m++){
        if(g.weight[i][m] == 1){
            j = m;
            break;
        }
    }
    if(j == 0){
        printf("cannot find the starting number!\n");
        return;
    }
    g.check_visit[i] = 1;
    cnt++;
    printf("%d ", i);
    while(cnt < g.num){
        if(i == end) break;
        for(int j = 1; j <= g.num; j++){
            if(g.weight[i][j] == 1){
                if(g.check_visit[j] == 1) continue;
                else{
                    g.check_visit[j] = 1;
                    enqueue(q, j);
                }
            }
        }
        i = dequeue(q);
        printf("%d ", i);
        cnt++;
    }
    if(g.num < end)
        printf("cannot find");
    else if(g.check_visit[end] == 0)
        printf("cannot find");
    close_queue(q);

    return;
}

stack * create_stack(int num){
    stack * s = (stack *)malloc(sizeof(stack));
    s->max_stack_size = num;
    s->top = -1;
    int * arr = (int *)malloc(sizeof(int)*s->max_stack_size);
    s->content = arr;

    return s;
}

void push(stack * s, int value){
    if(s->top + 1 == s->max_stack_size){
        printf("stack is full!\n");
        return;
    }
    s->top++;
    s->content[s->top] = value;

    return;
}

int pop(stack * s){
    if(s->top == -1){
        printf("stack is empty!\n");
        return 0;
    }
    return s->content[s->top--];
}

void close_stack(stack * s){
    free(s->content);
    free(s);

    return;
}

queue * create_queue(int size){
    queue * q  = (queue *)malloc(sizeof(queue));
    q->max_queue_size = size;
    int * arr = (int *)malloc(sizeof(int)*q->max_queue_size);
    q->content = arr;
    q->first = q->rear = q->qsize = 0;
}

void enqueue(queue * q, int value){
    if(q->qsize == q->max_queue_size){
        printf("queue is full!\n");
        return;
    }
    q->rear = ++q->rear%q->max_queue_size;
    q->content[q->rear] = value;
    q->qsize++;
}

int dequeue(queue * q){
    if(q->qsize == 0){
        printf("queue is empty!\n");
        return 0;
    }
    q->first = ++q->first%q->max_queue_size;
    int rtn = q->content[q->first];
    q->qsize--;

    return rtn;
}

void close_queue(queue * q){
    free(q->content);
    free(q);

    return;
}