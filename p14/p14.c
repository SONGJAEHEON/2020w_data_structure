#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct ListNode ListNode;
typedef ListNode * List;
typedef ListNode * Position;

typedef struct ListNode{
    ElementType Element;
    Position Next;
};

typedef struct HashTable{
    int TableSize;
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
    hs->TheLists = (List *)malloc(sizeof(ListNode)*indexnumber);
    int i;
    // for(i = 0; i < indexnumber; i++){
    //      hs->TheLists[i] = (List)malloc(sizeof(ListNode));
    // }

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
    Position p = Finde(Key, H);
    if(p == NULL){
        printf("%d insertion collision has been occurred with numebr 5\n", Key);
    }else{
        // 빈 칸 전의 리스트를 리턴 받음
        p->Element = Key;
        printf("%d is inserted\n", Key);
    }

    return;
}

Position Find(int Value, HashTable * H){
    bool dup = FALSE;
    int remainder = Value % (H->TableSize - 1);

    // 리스트에 원소가 있음
    while(H->TheLists[remainder] != -1){
        // 같은 걸 못 찾음
        if(H->TheLists[remainder] != Value) remainder++;
        // 같은 걸 찾음
        else dup = TRUE;
    }

    // 같은 걸 찾음
    if(dup == TRUE) return NULL;
    // 같은 걸 못 찾음, -1인 리스트 순서 전 차례 리턴
    else return H->TheLists[--remainder];
}