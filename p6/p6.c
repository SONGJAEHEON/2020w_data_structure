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
    }else if(X > T->Element){
        T->Right = Insert(X, T->Right);
    }else{
        printf("[Error] %d already in the tree!\n", X);
    }
    printf("%d inserted!", X);
    getHeight(T);
    printf("height calc\n");
    int l, r, _l, _r;
    if(T->Left == NULL){
        l = -1;
    }else{
        l = T->Left->Height;
    }
    if(T->Right == NULL){
        r = -1;
    }else{
        r = T->Right->Height;
    }
    if(l - r > 1){
        if(T->Left->Left == NULL){
            _l = -1;
        }else{
            _l = T->Left->Left->Height;
        }
        if(T->Left->Right == NULL){
            _r = -1;
        }else{
            _r = T->Left->Right->Height;
        }
        if(_l - _r > 0){
            // LL
            
            T = SingleRotateWithRight(T);
        }else if(_l - _r < 0){
            // LR
            
            T = DoubleRotateWithRight(T);
        }
    }else if(l - r < -1){
        if(T->Right->Left == NULL){
            _l = -1;
        }else{
            _l = T->Right->Left->Height;
        }
        if(T->Right->Right == NULL){
            _r = -1;
        }else{
            _r = T->Right->Right->Height;
        }
        if(_l - _r > 0){
            // RL
            
            T = DoubleRotateWithLeft(T);
        }else if(_l - _r < 0){
            // RR
            
            T = SingleRotateWithLeft(T);
        }
    }
    getHeight(T);
    // if(_l - _r )

    // if(T->Left != NULL){
    //     if(T->Left->Height == 1 && T->Right == NULL){
    //         if(X < T->Left->Element){
    //             printf("LL\n");
    //             T = SingleRotateWithRight(T);
    //         }else if(X > T->Left->Element){
    //             printf("LR\n");
    //             T = DoubleRotateWithRight(T);
    //         }
    //     }
    // }
    // if(T->Right != NULL){
    //     if(T->Right->Height == 1 && T->Left == NULL){
    //         if(X > T->Right->Element){
    //             printf("RR\n");
    //             T = SingleRotateWithLeft(T);
    //         }else if(X < T->Right->Element){
    //             printf("RL\n");
    //             T = DoubleRotateWithRight(T);
    //         }
    //     }
    // }
    // getHeight(T);
    // if(T->Left != NULL && T->Right != NULL){
    //     if(T->Left->Height - T->Right->Height > 1){
    //         if(X < T->Left->Element){
    //             printf("LL\n");
    //             T = SingleRotateWithRight(T);
    //         }else if(X > T->Left->Element){
    //             printf("LR\n");
    //             T = DoubleRotateWithRight(T);
    //         }
    //     }else if(T->Right->Height - T->Left->Height > 1){
    //         if(X > T->Right->Element){
    //             printf("RR\n");
    //             T = SingleRotateWithLeft(T);
    //         }else if(X < T->Right->Element){
    //             printf("RL\n");
    //             T = DoubleRotateWithRight(T);
    //         }
    //     }
    // }
    // if(T->Left != NULL){
    //     if(T->Left->Height == 1 && T->Right == NULL){
    //         if(X < T->Left->Element){
    //             printf("LL\n");
    //             T = SingleRotateWithRight(T);
    //         }else if(X > T->Left->Element){
    //             printf("LR\n");
    //             T = DoubleRotateWithRight(T);
    //         }
    //     }
    // }
    // if(T->Right != NULL){
    //     if(T->Right->Height == 1 && T->Left == NULL){
    //         if(X > T->Right->Element){
    //             printf("RR\n");
    //             T = SingleRotateWithLeft(T);
    //         }else if(X < T->Right->Element){
    //             printf("RL\n");
    //             T = DoubleRotateWithRight(T);
    //         }
    //     }
    // }
    // getHeight(T);
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
    if(T == NULL) return -1;
        l = getHeight(T->Left) + 1;
    // if(T->Left != NULL){
    // }
        r = getHeight(T->Right) + 1;
    // if(T->Right != NULL){
    // }
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
    printf("RR\n");
    Position child = node->Right;
    node->Right = child->Left;
    child->Left = node;

    return child;
}

Position SingleRotateWithRight(Position node){
    // type LL
    printf("LL\n");
    Position child = node->Left;
    node->Left = child->Right;
    child->Right = node;

    return child;
}

Position DoubleRotateWithLeft(Position node){
    // type RL
    printf("RL\n");
    node->Right = SingleRotateWithRight(node->Right);
    node = SingleRotateWithLeft(node);
    
    return node;
}

Position DoubleRotateWithRight(Position node){
    // type LR
    printf("LR\n");
    node->Left = SingleRotateWithLeft(node->Left);
    node = SingleRotateWithRight(node);

    return node;
}