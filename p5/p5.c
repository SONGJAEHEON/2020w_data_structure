#include <stdio.h>
#include <stdlib.h>

typedef struct Tree{
    int value;
    struct Tree* left;
    struct Tree* right;
}Tree;

Tree* insertNode(Tree* root, int key);
void printInorder(Tree* root);
void deleteTree(Tree* root);

void main(int argc, int* argv[]){
    FILE* fi = fopen(argv[1], "r");
    char cv;
    int key;

    Tree* root = NULL;

    while(!feof(fi)){
        fscanf(fi, "%c", &cv);
        switch(cv){
            case 'i':
                fscanf(fi, "%d", &key);
                root = insertNode(root, key);
                break;
            case 'p':
                fscanf(fi, "%c", &cv);
                if(cv == 'i') printInorder(root);
                printf('\n');
                break;
        }
    }
    deleteTree(root);
}

void deleteTree(Tree* root){
    if(root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

Tree* insertNode(Tree* root, int key){

}

void deleteTree(Tree* root){
    
}