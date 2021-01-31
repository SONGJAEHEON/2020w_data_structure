#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // To use strtok_r(char * string, const char * seps, char ** lasts)

#define TRUE    1;
#define FALSE   0;

typedef int ElementType;
typedef struct ListNode ListNode;
typedef ListNode * List;
typedef ListNode * Position;

struct ListNode{
    ElementType Element;
    Position Next;
};

typedef struct HashTable{
    int TableSize;
    int Capacity;
    List * TheLists;
} HashTable;

void Insert(int, HashTable *);
Position Find(int, HashTable *);

int main(int argc, char * argv[]){
    FILE * f;
    f = fopen(argv[1], "r");
    char index[100];
    int indexnumber;
    char * ptr1, * ptr2, * ptr3;
    char * ptrtmp[3];

    fgets(index, 100, f);
    ptr1 = strtok_r(index, " ", &ptrtmp[0]);

    indexnumber = atoi(ptr1);
    HashTable * hs;
    hs = (HashTable *)malloc(sizeof(HashTable));
    hs->TableSize = indexnumber;
    hs->Capacity = 0;
    hs->TheLists = (List *)malloc(sizeof(ListNode)*(indexnumber));
    int i;
    for(i = 0; i < indexnumber; i++){
        hs->TheLists[i] = (List)malloc(sizeof(ListNode));
    }

    fgets(index, 100, f);
    ptr2 = strtok_r(index, " ", &ptrtmp[1]);
    while(ptr2 != NULL){
        indexnumber = atoi(ptr2);
        Insert(indexnumber, hs);
        ptr2 = strtok_r(NULL, " ", &ptrtmp[1]);
    }

    Position tmp;
    fgets(index, 100, f);
    ptr3 = strtok_r(index, " ", &ptrtmp[2]);
    while(ptr3 != NULL){
        indexnumber = atoi(ptr3);
        tmp = Find(indexnumber, hs);
        if(tmp == NULL)
            printf("%d is not in the table\n", indexnumber);
        else printf("%d is in the table\n", indexnumber);
        ptr3 = strtok_r(NULL, " ", &ptrtmp[2]);
    }

    return 0;
}

void Insert(ElementType Key, HashTable * H){
    int remainder = Key % (H->TableSize), rm;
    int dup = FALSE;
    if(H->Capacity == H->TableSize){
        printf("HashTable is full!\n");
        return;
    }
    while(H->TheLists[remainder]->Element != 0){
        if(Key == H->TheLists[remainder]->Element){
            dup = 1;
            break;
        }
        printf("%d insertion collision has been occured with the number %d\n", Key, H->TheLists[remainder]->Element);
        remainder = ++remainder % H->TableSize;
    }
    if(dup == 1){
        printf("%d is already in the table\n", Key);
        return;
    }
    H->TheLists[remainder]->Element = Key;
    H->Capacity++;
    rm = (remainder + 29) % H->TableSize;
    H->TheLists[rm]->Next = H->TheLists[remainder];
    printf("%d is inserted at address %d\n", Key, remainder);

    return;
}

Position Find(int Value, HashTable * H){
    int dup = FALSE;
    int remainder = Value % (H->TableSize);

    // 리스트에 원소가 있음
    while(H->TheLists[remainder]->Element != 0){
        // 같은 걸 못 찾음
        if(H->TheLists[remainder]->Element != Value){
            remainder = ++remainder % H->TableSize;
        }
        // 같은 걸 찾음
        else{
            dup = TRUE;
            break;
        }
    }

    // 같은 걸 찾음
    if(dup == 1){
        return H->TheLists[remainder];
    }
    // 같은 걸 못 찾음, -1인 리스트 순서 전 차례 리턴
    else{
        return NULL;
    }
}