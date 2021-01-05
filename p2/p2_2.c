#include <stdio.h>

int main(int argc, const char** argv){
    // '\n'과 'NULL' 문자를 위해 길이 2 추가
    char arr[32];

    printf("enter your name\n");
    fgets(arr, sizeof(arr), stdin);
    printf("you name is %s", arr);

    return 0;
}