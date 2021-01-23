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

void main(int argc, char* argv[]){
    FILE* fi = fopen(argv[1], "r");
    char cv;
    int key;

    Tree* root = NULL;
    while(!feof(fi)){
        // to avoid reading the last line twice
        if(fread(&cv, 1, 1, fi) == 0)break;
        else fseek(fi, -1, SEEK_CUR);
        
        fscanf(fi, "%c", &cv);
        switch(cv){
            case 'i':
                fscanf(fi, "%d", &key);
                root = insertNode(root, key);
                break;
            case 'p':
                fscanf(fi, "%c", &cv);
                if(cv == 'i') printInorder(root);
                putchar('\n');
                break;
        }
    }
    deleteTree(root);
    fclose(fi);
}

void deleteTree(Tree* root){
    if(root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

Tree* insertNode(Tree* root, int key){
    if(root == NULL){
        Tree * tmp = (Tree *)malloc(sizeof(Tree));
        tmp->value = key;
        tmp->left = NULL;
        tmp->right = NULL;
        printf("insert %d\n", key);

        return tmp;
    }else{
        if(key < root->value){
            root->left = insertNode(root->left, key);
        }else if(key > root->value){
            root->right = insertNode(root->right, key);
        }else{
            printf("Insertion Error : There is already %d in the tree.\n", key);
        }

        return root;
    }
}

void printInorder(Tree* root){
    if(root == NULL) return;

    printInorder(root->left);
    printf("%d ", root->value);
    printInorder(root->right);

    return;
}