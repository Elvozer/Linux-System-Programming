#include<dirent.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

char *concatenatePath(char *s1, char *s2){
    int sS1 = strlen(s1);
    int sS2 = strlen(s2);
    char *str = (char*)malloc((sS1+sS2+2)*sizeof(char));
    for(int i=0; i<sS1; i++){
        str[i] = s1[i];
    }
    str[sS1] = '/';
    for(int i=0; i<sS2; i++){
        str[++sS1] = s2[i];
    }
    str[++sS1] = '\0';
    return str;
}

bool filter(char *path, char *word){ 
 FILE *ptr = fopen(path, "r");
    if (ptr == NULL){
        perror("Loi chuong trinh:");
        return false;
    }
    char buffer[512];
    while(fgets(buffer, sizeof(buffer), ptr) != NULL){
        if(strstr(buffer, word) != NULL){
            fclose(ptr);
            return true;
        }
    }
    fclose(ptr);
    return false;
}

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Nhap thieu tham so.");
        return 1;
    }
    DIR *dirptr = opendir(argv[2]);
    struct dirent *entry;
    while(entry = readdir(dirptr)){
        char *path = concatenatePath(argv[2], entry->d_name);
        if(filter(path, argv[1])){
            printf("%s\n", entry->d_name);
        }
        free(path);
    }
    closedir(dirptr);
    return 0;
}