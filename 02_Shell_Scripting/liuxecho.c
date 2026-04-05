#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Nhap thieu tham so\n");
        return 1;
    }
    int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd<0){
        perror("Loi chuong trinh:");
        return 1;
    }
    int len = strlen(argv[1]);
    write(fd, argv[1], len);
    close(fd);
    return 0;
}