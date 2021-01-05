#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char** argv){
    // 2명 이상의 이름이 입력되어야 한다.
    int num = atoi(argv[1]);
    int cha;
    int i = 0;
    // 한 명의 이름 글자 수 제한 확인을 위한 count 변수(30자)
    int cnt = 0;

    // char 배열 동적할당
    char* arr = (char*)malloc(sizeof(char)*30*num);
    if(num < 2){
        printf("the number of students should be more than 1\n");
        return 0;
    }
    while(1){
        // 한 명의 이름 글자 수가 30을 초과
        if(cnt > 30){
            printf("the length of the user name should be up to 30 characters\n");
            return 0;
        }
        cha = getchar();
        if(cha == ' ' || cha == '\0'){
            cnt = 0;
        }else if(cha == '\n'){
            arr[i] = '\n';
            break;
        }
        arr[i] = (char) cha;
        i++;
        cnt++;
    }
    i = 0;
    while(1){
        cha = arr[i];
        if(cha == ' ' || cha == '\0'){
            printf("\n");
            i++;
            continue;
        }else if(cha == '\n'){
            printf("\n");
            break;
        }
        putchar(cha);
        i++;
    }

    return 0;
}