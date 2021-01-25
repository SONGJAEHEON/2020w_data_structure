#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Graph{
    int size;
    int ** vertices;
    Node * nodes;
} Graph;

typedef struct Node{
    int vertex;
    int dist; //distance
    int prev;
} Node;

typedef struct Heap{
    int Capacity;
    int Size;
    Node * Element;
} Heap;

Graph CreateGraph(int size);
void printShortestPath(Graph g);
Heap * createMinHeap(int heapSize);
void insertToMinHeap(Heap * minHeap, int vertex, int distance);
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
        fscnf(fi, "%d-%d-%d", &node1, &node2, &weight);
        g.vertices[node1][node2] = weight;
        temp = fgetc(fi);
    }
    printShortestPath(g);
}