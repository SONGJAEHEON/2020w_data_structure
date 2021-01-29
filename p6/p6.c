#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct AVLNode * AVLTree;
typedef AVLTree Position;

struct AVLNode{
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

AVLTree Insert(ElementType X, AVLTree T);
int getHeight(AVLTree T);
void printInorder(AVLTree T);
void DeleteTree(AVLTree T);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);

int main(int argc, char** argv){
    FILE * fp = fopen(argv[1], "r");
    AVLTree myTree = NULL;
    int num;

    if(fp == NULL){
        printf("There is no file : %s\n", argv[1]);
        exit(-1);
    }
    while(fscanf(fp, "%d", &num) != EOF){
        myTree = Insert(num, myTree);
        printInorder(myTree);
        printf("\n");
    }

    DeleteTree(myTree);

    return 0;
}

AVLTree Insert(ElementType X, AVLTree T){
    if(T == NULL){
        AVLTree newNode = (AVLTree)malloc(sizeof(struct AVLNode));
        newNode->Element = X;
        newNode->Left = NULL;
        newNode->Right = NULL;
        newNode->Height = 0;
        T = newNode;
    }else if(X < T->Element){
        T->Left = Insert(X, T->Left);
        printf("left inserted\n");
    }else if(X > T->Element){
        T->Right = Insert(X, T->Right);
    }else{
        printf("[Error] %d already in the tree!\n", X);
    }
    getHeight(T);
    // printf("5 : %d\n", T->Left->Height);
    // if(T->Left->Height == 1 && T->Right == NULL){
    //     if(X < T->Left->Element){
    //         printf("LL\n");
    //         SingleRotateWithRight(T);
    //     }else if(X > T->Left->Element){
    //         printf("LR\n");
    //         DoubleRotateWithRight(T);
    //     }
    // }else if(T->Right->Height == 1 && T->Left == NULL){
    //     if(X > T->Right->Element){
    //         printf("RR\n");
    //         SingleRotateWithLeft(T);
    //     }else if(X < T->Right->Element){
    //         printf("RL\n");
    //         DoubleRotateWithRight(T);
    //     }
    // }
    // if(getHeight(T->Left) > getHeight(T->Right) + 1){
    //     if(X < T->Left->Element){
    //         printf("LL\n");
    //         SingleRotateWithRight(T);
    //     }else if(X > T->Left->Element){
    //         printf("LR\n");
    //         DoubleRotateWithRight(T);
    //     }
    // }else if(getHeight(T->Right) > getHeight(T->Left) + 1){
    //     if(X > T->Right->Element){
    //         printf("RR\n");
    //         SingleRotateWithLeft(T);
    //     }else if(X < T->Right->Element){
    //         printf("RL\n");
    //         DoubleRotateWithRight(T);
    //     }
    // }

    return T;
}
int getHeight(AVLTree T){
    int l = 0, r = 0;
    if(T == NULL) return 0;
    if(T->Left != NULL){
        l = getHeight(T->Left) + 1;
    }
    if(T->Right != NULL){
        r = getHeight(T->Right) + 1;
    }
    if(l > r){
        T->Height = l;
    }else{
        T->Height = r;
    }

    return T->Height;
}
// int getHeight(AVLTree T){
//     int l = -1, r = -1;
//     if(T == NULL) return -1;
//     if(T->Left != NULL){
//         l = getHeight(T->Left);
//     }
//     if(T->Right != NULL){
//         r = getHeight(T->Right);
//     }
//     if(l > r){
//         T->Height = l + 1;
//     }else{
//         T->Height = r + 1;
//     }

//     return T->Height;
// }

void printInorder(AVLTree T){
    if(T == NULL) return;
    printInorder(T->Left);
    printf("%d(%d) ", T->Element, T->Height);
    printInorder(T->Right);

    return;
}

void DeleteTree(AVLTree T){
    if(T->Left != NULL){
        DeleteTree(T->Left);
    }
    if(T->Right != NULL){
        DeleteTree(T->Right);
    }
    free(T);

    return;
}

Position SingleRotateWithLeft(Position node){
    // type RR
    Position child = node->Right;
    node->Right = child->Left;
    child->Left = node;

    return child;
}

Position SingleRotateWithRight(Position node){
    // type LL
    Position child = node->Left;
    node->Left = child->Right;
    child->Right = node;

    return child;
}

Position DoubleRotateWithLeft(Position node){
    // type RL
    SingleRotateWithRight(node->Right);
    Position p = SingleRotateWithLeft(node);

    return p;
}

Position DoubleRotateWithRight(Position node){
    // type LR
    SingleRotateWithLeft(node->Left);
    Position p = SingleRotateWithRight(node);

    return p;
}