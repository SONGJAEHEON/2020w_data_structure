#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int vertex;
    int dist; //distance
    int prev;
} Node;

typedef struct Graph{
    int size;
    int ** vertices;
    Node * nodes;
} Graph;

typedef struct Heap{
    int Capacity;
    int Size;
    Node * Element;
} Heap;

Graph CreateGraph(int size);
void printShortestPath(Graph g);
void print(Graph g, int * cost, int vertex);
Heap * createMinHeap(int heapSize);
void insertToMinHeap(Heap * minHeap, int vertex, int distance, int prev);
Node deleteMin(Heap * minHeap);

void main(int argc, char * argv[]){
    FILE * fi = fopen(argv[1], "r");
    Graph g;
    int size;
    fscanf(fi, "%d\n", &size);
    g = CreateGraph(size+1);
    char temp = 0;
    while(temp != '\n'){
        int node1, node2, weight;
        fscanf(fi, "%d-%d-%d", &node1, &node2, &weight);
        g.vertices[node1][node2] = weight;
        temp = fgetc(fi);
    }
    printShortestPath(g);

    return;
}

Graph CreateGraph(int size){
    Graph * g = (Graph *)malloc(sizeof(Graph));
    g->size = size;
    Node * arr1 = (Node *)malloc(sizeof(Node)*g->size);
    for(int i = 0; i < g->size; i++){
        arr1[i].vertex = i;
        arr1[i].dist = 255;
        arr1[i].prev = 0;
    }
    int ** arr2 = (int **)malloc(sizeof(int *)*g->size);
    for(int i = 0; i < g->size; i++){
        arr2[i] = (int *)malloc(sizeof(int)*g->size);
    }
    for(int i = 0; i < g->size; i++){
        for(int j = 0; j < g->size; j++){
            arr2[i][j] =  0;
        }
    }
    g->nodes = arr1;
    g->vertices = arr2;

    return * g;
}

void printShortestPath(Graph g){
    int i = 1;
    Node n;
    Heap * h = createMinHeap(g.size*g.size);
    do{
        for(int j = 1; j <= g.size; j++){
            if(g.vertices[i][j] != 0){
                insertToMinHeap(h, j, g.vertices[i][j], i);
            }
        }
        n = deleteMin(h);
        if(n.dist < g.nodes[n.vertex].dist){
            g.nodes[n.vertex].dist = n.dist;
            g.nodes[n.vertex].prev = n.prev;
        }
        i = n.vertex;
    } while(h->Capacity > 0);
    for(int k = 2; k < g.size; k++){
        int cost = 0;
        int * cst = &cost;
        printf("1");
        print(g, cst, k);
        printf(" (cost : %d)\n", cost);
    }
    free(h);

    return;
}

void print(Graph g, int * cost, int vertex){
    if(g.nodes[vertex].prev == 1){
        * cost += g.nodes[vertex].dist;
        printf("->%d", vertex);
        return;
    }
    print(g, cost, g.nodes[vertex].prev);
    * cost += g.nodes[vertex].dist;
    printf("->%d", vertex);

    return;
}

Heap * createMinHeap(int heapSize){
    Heap * h = (Heap *)malloc(sizeof(Heap));
    Node * arr = (Node *)malloc(sizeof(Node)*heapSize+1);
    h->Capacity = 0;
    h->Size = heapSize+1;
    h->Element = arr;

    return h;
}

void insertToMinHeap(Heap * minHeap, int vertex, int distance, int previous){
    if(minHeap->Capacity == minHeap->Size){
        printf("minHeap is full!\n");
        return;
    }

    minHeap->Capacity++;
    int i = minHeap->Capacity;
    while(i > 1 && distance < minHeap->Element[i/2].dist){
        minHeap->Element[i] = minHeap->Element[i/2];
        i /= 2;
    }
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->dist = distance;
    newNode->prev = previous;
    minHeap->Element[i] = * newNode;

    return;
}

Node deleteMin(Heap * minHeap){
    if(minHeap->Capacity == 0){
        printf("minHeap is empty\n");
        exit(1);
    }
    Node rtn = minHeap->Element[1];
    minHeap->Element[1] = minHeap->Element[minHeap->Capacity];
    int i = 1, chck = 1, comp = minHeap->Element[minHeap->Capacity--].dist, comp2;
    while(i <= minHeap->Capacity && chck){
        if(minHeap->Capacity == 2*i){
            if(minHeap->Element[2*i].dist < comp){
                minHeap->Element[i] = minHeap->Element[2*i];
                i *= 2;
            }else{
                chck = 0;
            }
        }else{
            if(minHeap->Element[2*i].dist > minHeap->Element[2*i+1].dist){
                comp2 = 2*i;
            }else{
                comp2 = 2*i + 1;
            }
            if(comp2 < comp){
                minHeap->Element[i] = minHeap->Element[comp2];
                i = comp2;
            }else{
                chck = 0;
            }
        }
    }
    
    return rtn;
}