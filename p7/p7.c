#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct HeapStruct{
    int Capacity;
    int Size;
    ElementType * Elements;
} Heap;

Heap * CreateHeap(int heapSize);
void Insert(Heap * heap, int value);
int Find(Heap * heap, int value);
int DeleteMax(Heap * heap);
void PrintHeap(Heap * heap);

void main(int argc, char * argv[]){
    printf("0");
    FILE * fi = fopen(argv[1], "r");
    printf("1");
    char cv;
    Heap * maxHeap;
    int heapSize, key;
    printf("2");
    while(!feof(fi)){
        fscanf(fi, "%c", &cv);
        printf("3");
        switch(cv){
            case 'n':
                fscanf(fi, "%d", &heapSize);
                maxHeap = CreateHeap(heapSize);
                break;
            case 'i':
                fscanf(fi, "%d", &key);
                Insert(maxHeap, key);
                break;
            case 'd':
                DeleteMax(maxHeap);
                break;
            case 'p':
                PrintHeap(maxHeap);
                break;
            case 'f':
                fscanf(fi, "%d", &key);
                if(Find(maxHeap, key))
                    printf("%d is in the tree.\n", key);
                else
                    printf("%d is not in the tree.\n", key);
                break;
        }
    }
    free(maxHeap);

    return;
}

Heap * CreateHeap(int heapSize){
    Heap * h = (Heap *)malloc(sizeof(int)*(heapSize+2));
    h->Size = heapSize;
    h->Capacity = 0;

    return h;
}

void Insert(Heap * heap, int value){
    if(heap->Capacity >= heap->Size){
        printf("Insertion Error : Max Heap is full.\n");
    }else if(heap->Capacity == 0){
        heap->Elements[1] = value;
    }else{
        int parent, child;
        child = ++heap->Capacity;
        parent = child / 2;
        heap->Elements[heap->Capacity] = value;
        while(child > 1 && heap->Elements[parent] < heap->Elements[child]){
            heap->Elements[child] = heap->Elements[parent];
            parent = parent / 2;
            child = parent * 2;
        }
        heap->Elements[parent] = value;
    }
    heap->Capacity++;
    printf("insert %d\n", value);

    return;
}

int Find(Heap * heap, int value){
    for(int i = 1; i <= heap->Size; i++){
        if(heap->Elements[i] == value) return 1;
    }

    return 0;
}

int DeleteMax(Heap * heap){
    if(heap->Capacity == 0){
        printf("Deletion Error : Max heap is empty!\n");
    }
    int val = 1, big, max = heap->Elements[1];
    heap->Elements[1] = heap->Elements[heap->Capacity];
    
    while(val <= heap->Capacity && heap->Elements[2*val]){
        if(2*val+1 > heap->Capacity){
            big = 2 * val;
        }else{
            if(heap->Elements[2*val] > heap->Elements[2*val+1]){
                big = 2 * val;
            }else{
                big = 2 * val + 1;
            }
        }
        if(heap->Elements[big] > heap->Elements[val]){
            heap->Elements[val] = heap->Elements[big];
        }else{
            break;
        }
    }
    heap->Capacity--;

    return max;
}

void PrintHeap(Heap * heap){
    if(heap->Capacity == 0){
        printf("Print Error : Maxheap is empty!\n");
    }else{
        int i = 1;
        while(i <= heap->Size){
            printf("%d ",heap->Elements[i]);
        }
        putchar('\n');
    }

    return;
}