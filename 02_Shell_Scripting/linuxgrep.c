#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Nhap thieu tham so.");
        return 1;
    }
    FILE *ptr = fopen(argv[2], "r");
    if (ptr == NULL){
        perror("Loi chuong trinh:");
        return 1;
    }
    char buffer[512];
    while(fgets(buffer, sizeof(buffer), ptr) != NULL){
        if(strstr(buffer,argv[1]) != NULL){
            printf("%s", buffer);
        }
    }
    fclose(ptr);
    return 0;
}