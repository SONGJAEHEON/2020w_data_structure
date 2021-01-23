#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _DisjointSet{
    int size_maze;
    int * ptr_arr;
} DisjointSets;

void init(DisjointSets * sets, DisjointSets * maze_print, int num);
void union(DisjointSets * sets, int i, int j);
int find(DisjointSets * sets, int i);
void createMaze(DisjointSets * sets, DisjointSets * maze_print, int num);
void printMaze(DisjointSets * sets, int num);
void freeMaze(DisjointSets * sets, DisjointSets * maze_print);

int main(int argc, char * argv[]){
    int num, i;
    FILE * fi = open(fi, "r");
    DisjointSets * sets, * maze_print;
    fscanf(fi, "%d", &num);
    sets = (DisjointSets *)malloc(sizeof(DisjointSets));
    maze_print = (DisjointSets *)malloc(sizeof(DisjointSets));
    init(sets, maze_print, num);
    createMaze(sets, maze_print, num);
    printMaze(maze_print, num);
    freeMaze(sets, maze_print);

    return 0;
}

void init(DisjointSets * sets, DisjointSets * maze_print, int num){
    sets->size_maze = num;
    sets->ptr_arr = (int *)malloc(sizeof(int)*num*num);

    maze_print->size_maze = num;
    maze_print->ptr_arr = (int *)malloc(sizeof(int)*)
}