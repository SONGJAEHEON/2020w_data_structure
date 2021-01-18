#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node{
    ElementType element;
    Position next;
};

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void Insert(ElementType X, List L, Position P);
void PrintList(List L);
void Delete(ElementType X, List L);
Position Find(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
void DeleteList(List L);

int main(int argc, char* argv[]){
    char command;
    int key1, key2;
    FILE* input;
    Position header;
    Position tmp;
    if(argc == 1){
        input = fopen("input.txt", "r");
    }else{
        input = fopen(argv[1], "r");
    }
    header = MakeEmpty(header);
    while(1){
        command = fgetc(input);
        if(feof(input))break;
        switch(command){
            case 'i':
                fscanf(input, "%d %d", &key1, &key2);
                tmp = Find(key2, header);
                Insert(key1, header, tmp);
                break;
            case 'd':
                fscanf(input, "%d", &key1);
                Delete(key1, header);
                break;
            case 'f':
                fscanf(input, "%d", &key1);
                tmp = FindPrevious(key1, header);
                if(IsLast(tmp, header)){
                    printf("Could not find %d in the list\n", key1);
                }else{
                    if(tmp->element > 0){
                        printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
                    }else{
                        printf("Key of th previous node of %d is header.\n", key1);
                    }
                }
                break;
            case 'p':
                PrintList(header);
                break;
            default:
            break;
        }
    }
    DeleteList(header);
    fclose(input);
    return 0;
}
// List MakeEmpty(List L);
// int IsEmpty(List L);
// int IsLast(Position P, List L);
// void Insert(ElementType X, List L, Position P);
// void PrintList(List L);
// void Delete(ElementType X, List L);
// Position Find(ElementType X, List L);
// Position FindPrevious(ElementType X, List L);
// void DeleteList(List L);

List MakeEmpty(List L){
    L->element = 0;
    L->next = NULL;

    return L;
}

int Isempty(List L){
    return (L->next == NULL);
}

int IsLast(Position P, List L){
    return (P->next == NULL || P == NULL);
}

void Insert(ElementType X, List L, Position P){
    if(P == NULL){
        printf("Insertion(%d) Failed : cannot find the location to be inserted\n", X);
    }else{
        PtrToNode newNode = (PtrToNode)malloc(sizeof(struct Node));
        newNode->element = X;
        newNode->next = P->next;
        P->next = newNode;
    }

    return;
}

void PrintList(List L){
    while(L->next != NULL){
        printf("key:%d\t", L->element);
        L = L->next;
    }
    printf("key:%d\t", L->element);

    return;
}

void Delete(ElementType X, List L){
    Position p = FindPrevious(X, L);
    Position tmp = p->next;
    if(p == NULL){
        printf("Deletion failed : element %d is not in the list\n", X);
    }else{
        p->next = p->next->next;
        free(tmp);
    }

    return;
}

Position Find(ElementType X, List L){
    Position tmp;
    tmp = L;

    //if it is '-1', return header.
    if(X == -1) return tmp;

    if(IsEmpty(L)){
        printf("Could not find %d in the list\n", X);
        return NULL;
    }
    while(tmp->element != X){
        if(tmp->next == NULL){
            printf("Could not find %d in the list\n", X);
            return NULL;
        }
        else tmp = tmp->next;
    }

    return tmp;
}

Position FindPrevious(ElementType X, List L){
    Position tmp;
    tmp = L;
    if(IsEmpty(L)){
        printf("Could not find %d in the list\n", X);
        return NULL;
    }
    while(tmp->next->element != X){
        if(tmp->next->next == NULL){
            printf("Could not find %d in the list\n", X);
            return NULL;
        }
        else tmp = tmp->next;
    }
    
    return tmp;
}

void DeleteList(List L){
    List tmp = NULL;
    while(L->next != NULL){
        tmp = L;
        L = L->next;
        free(tmp);
    }
    free(L);

    return;
}