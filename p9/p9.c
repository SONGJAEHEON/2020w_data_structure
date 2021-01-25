#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet{
    int size_maze;
    int * ptr_arr;
} DisjointSets;

void init(DisjointSets * sets, DisjointSets * maze_print, int num);
void unite(DisjointSets * sets, int i, int j);
int find(DisjointSets * sets, int i);
void createMaze(DisjointSets * sets, DisjointSets * maze_print, int num);
void printMaze(DisjointSets * sets, int num);
void freeMaze(DisjointSets * sets, DisjointSets * maze_print);

int main(int argc, char * argv[]){
    int num, i;
    FILE * fi = fopen(argv[1], "r");
    DisjointSets * sets, * maze_print;
    fscanf(fi, "%d", &num);
    sets = (DisjointSets *)malloc(sizeof(DisjointSets));
    maze_print = (DisjointSets *)malloc(sizeof(DisjointSets));
    init(sets, maze_print, num);
    createMaze(sets, maze_print, num);
    printMaze(maze_print, num);
    freeMaze(sets, maze_print);
    fclose(fi);

    return 0;
}

void init(DisjointSets * sets, DisjointSets * maze_print, int num){
    sets->size_maze = num;
    sets->ptr_arr = (int *)malloc(sizeof(int)*(num*num+1));
    for(int i = 1; i <= num*num; i++){
        sets->ptr_arr[i] = -1;
    }

    maze_print->size_maze = num;
    maze_print->ptr_arr = (int *)malloc(sizeof(int)*(4*num*num+4*num+1));
    int j = 0;
    while(j < 4*num*num+4*num+1){
        if(j/(2*num+1)%2 == 0){
            if(j%(2*num+1)%2 == 0) maze_print->ptr_arr[j] = 0;
            else maze_print->ptr_arr[j] = -1;
        }else{
            if(j%(2*num+1)%2 == 0) maze_print->ptr_arr[j] = -1;
            else maze_print->ptr_arr[j] = 0;
        }
        j++;
    }
    maze_print->ptr_arr[2*num+1] = 0;
    maze_print->ptr_arr[4*num*num+2*num-1] = 0;

    return;
}

void unite(DisjointSets * sets, int i, int j){
    sets->ptr_arr[j] = i;
}

int find(DisjointSets * sets, int i){
    while(sets->ptr_arr[i] != -1){
        i = sets->ptr_arr[i];
    }

    return i;
}

void createMaze(DisjointSets * sets, DisjointSets * maze_print, int num){
    // generate seed
    srand((unsigned int)time(NULL));

    // rand() function returns integer from 0 to 32767
    int p = num * num;
    int a, b;
    
    while(find(sets, 1) != find(sets, p)){
        int x = rand() % p + 1;
        int y = rand() % p + 1;
        if(x != y){
            a = find(sets, x);
            b = find(sets, y);
            if((x+1 == y) && (x-1)/num == (y-1)/num){
                if(a != b){
                    sets->ptr_arr[b] = a;
                    maze_print->ptr_arr[(2*num+1)*((x-1)/num*2+1)+((x%num)*2)] = 0;
                }
            }else if((x-1 == y) && (x-1)/num == (y-1)/num){
                if(a != b){
                    sets->ptr_arr[b] = a;
                    maze_print->ptr_arr[(2*num+1)*((y-1)/num*2+1)+((y%num)*2)] = 0;
                }
            }else if((x+num) == y){
                if(a != b){
                    sets->ptr_arr[b] = a;
                    maze_print->ptr_arr[(2*num+1)*((x-1)/num+1)*2+((x-1)%num*2)+1] = 0;
                }
            }else if((x-num) == y){
                if(a != b){
                    sets->ptr_arr[b] = a;
                    maze_print->ptr_arr[(2*num+1)*((y-1)/num+1)*2+((y-1)%num*2)+1] = 0;
                }
            }
        }
    }

    return;
}

void printMaze(DisjointSets * sets, int num){
    int i = 0;
    while(i < 4*num*num+4*num+1){
        if(i/(2*num+1)%2 == 0){
            if(sets->ptr_arr[i] == -1) printf("─");
            else putchar(' ');
        }else{
            if(sets->ptr_arr[i] == -1) printf("│");
            else putchar(' ');
        }
        i++;
        if(i%(2*num+1) == 0) putchar('\n');
    }

    return;
}

void freeMaze(DisjointSets * sets, DisjointSets * maze_print){
    free(sets);
    free(maze_print);

    return;
}
