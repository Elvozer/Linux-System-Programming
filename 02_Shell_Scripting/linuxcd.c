#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Nhap thieu tham so.\n");
        return 1;
    }
    char path[1024];
    getcwd(path, sizeof(path));
    printf("Duong dan hien tai la: %s\n", path);
    if(chdir(argv[1]) == 0){
        getcwd(path, sizeof(path));
        printf("Duong dan sau do la: %s\n", path);
        return 0;
    }
    else{
        printf("Chuyen vi tri khong thanh cong.");
        return 1;
    }
}