#define _DEFAULT_SOURCE

#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>

int main(int argc, char *argv[]){
    if (argc != 2){
        perror("Nhap thieu tham so");
        return 1;
    }
    DIR *dir = opendir(argv[1]);
    if (dir == NULL){
        perror("Loi mo thu muc");
        return 1;
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL){
        if(*(entry->d_name) == '.'){
            continue;
        }
        printf("%s ", entry->d_name);
    }
    printf("\n");
    closedir(dir);
    return 0;
}