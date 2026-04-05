#include<stdio.h>
#include<sys/stat.h>
#include<string.h>

int main(){
    struct stat datfil;
    char filename[512], buffer[512];
    printf("Nhap ten file vao duoi day:\n");
    scanf("%s", filename);
    if((stat(filename, &datfil))<0){
        perror("Loi chuong trinh.");
        return 1;
    }
    printf("Kich thuoc file la: %ld bytes\n", datfil.st_size);
    printf("Quyen truy cap la: %o\n", datfil.st_mode & 0777);
    return 0;
}