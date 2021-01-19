#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack{
    int* key;
    int top;
    int max_stack_size;
} Stack;

Stack* CreateStack(int max);
void Push(Stack* S, int X);
int Pop(Stack* S);
void DeleteStack(Stack* S);
int IsEmpty(Stack* S);
int IsFull(Stack* S);

void main(int argc, char* argv[]){
    FILE* fi = fopen(argv[1], "r");

    Stack* stack;
    char input_str[101];
    int max, i = 0, a, b, result;
    double d;
    char c = '0';

    fgets(input_str, 101, fi);
    max = strlen(input_str);

    // operations
    stack = CreateStack(max);
    printf("Top numbers :");
    c = input_str[i];
    while(c != '#'){
        switch(c){
            case '+':
                b = Pop(stack);
                a = Pop(stack);
                if(a==0 || b==0) break;
                Push(stack, a+b);
                break;
            case '-':
                b = Pop(stack);
                a = Pop(stack);
                if(a==0 || b==0) break;
                Push(stack, a-b);
                break;
            case '*':
                b = Pop(stack);
                a = Pop(stack);
                if(a==0 || b==0) break;
                // int 범위 초과 확인
                d = (double)a * b;
                if(d > 2147483647) d = 2147483647;
                Push(stack, (int)d);
                break;
            case '/':
                b = Pop(stack);
                a = Pop(stack);
                if(a==0 || b==0) break;
                Push(stack, a/b);
                break;
            case '%':
                b = Pop(stack);
                a = Pop(stack);
                if(a==0 || b==0) break;
                Push(stack, a%b);
                break;
            default:
                a = (int)c-48;
                if(a == 0) break;
                Push(stack, a);
                break;
        }
        result = Pop(stack);
        printf("%d ", result);
        Push(stack, result);
        i++;
        //길이 초과 에러 방지
        if(i > max-1) break;
        c = input_str[i];
    }

    printf("\nevaluation result : %d\n", result);
    fclose(fi);
    DeleteStack(stack);
}

Stack* CreateStack(int max){
    Stack* S = NULL;
    S = (Stack*)malloc(sizeof(max));
    S->key = (int*)malloc(sizeof(int)*max);
    S->max_stack_size = max;
    S->top = -1;

    return S;
}

void Push(Stack* S, int X){
    if(S->top >= S->max_stack_size){
        printf("error : stack is full\n");
        return;
    }else{
        S->top++;
        S->key[S->top] = X;
    }

    return;
}

int Pop(Stack* S){
    if(S->top <= -1){
        printf("error : stack is empty\n");
        return 0;
    }else{
        S->top--;
    }

    return S->key[S->top+1];
}

void DeleteStack(Stack* S){
    free(S->key);
    free(S);

    return;
}


int IsEmpty(Stack* S){
    return (S->top == -1);
}

int IsFull(Stack* S){
    return (S->top >= S->max_stack_size-1);
}