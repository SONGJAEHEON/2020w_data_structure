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
    FILE * fi = fopen(argv[1], "r");
    char cv;
    Heap * maxHeap;
    int heapSize, key;
    while(!feof(fi)){
        // to avoid reading the last line twice.
        if(fread(&cv, 1, 1, fi) == 0)break;
        else fseek(fi, -1, SEEK_CUR);

        fscanf(fi, "%c", &cv);
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

    free(maxHeap->Elements);
    free(maxHeap);

    return;
}

Heap * CreateHeap(int heapSize){
    Heap * h = (Heap *)malloc(sizeof(Heap));
    h->Size = heapSize;
    h->Capacity = 0;
    h->Elements = (ElementType *)malloc(sizeof(int)*heapSize);

    return h;
}

void Insert(Heap * heap, int value){
    if(heap->Capacity >= heap->Size){
        printf("Insertion Error : Max Heap is full.\n");
    }else if(heap->Capacity == 0){
        heap->Elements[1] = value;
        heap->Capacity++;
        printf("insert %d\n", value);
    }else if(Find(heap, value)){
            printf("%d is already in the tree.\n", value);
    }else{
        int parent, child;
        child = ++heap->Capacity;
        parent = child / 2;
        heap->Elements[heap->Capacity] = value;
        while(child > 1 && heap->Elements[parent] < value){
            heap->Elements[child] = heap->Elements[parent];
            child = child / 2;
            parent = child / 2;;
        }
        heap->Elements[child] = value;
        printf("insert %d\n", value);
    }
    
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

        return 0;
    }
    int val = 1, big, tmp, max = heap->Elements[1];
    heap->Elements[1] = heap->Elements[heap->Capacity];
    
    while(2*val <= heap->Capacity){
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
            tmp = heap->Elements[val];
            heap->Elements[val] = heap->Elements[big];
            heap->Elements[big] = tmp;
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
        for(int i = 1; i <= heap->Capacity; i++){
            printf("%d ", heap->Elements[i]);
        }
        putchar('\n');
    }

    return;
}