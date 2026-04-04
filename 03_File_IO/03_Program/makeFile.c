#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    int i;
    printf("Hay lua chon che do tao file:\n1. Tao file va viet noi dung vao file tu ban phim.\n2. Tao file va copy noi dung tu file khac vao.\nLua chon: ");
    scanf("%d", &i);
    while(getchar() != '\n');
    if(i==1){
        char bufferOpen[512];
        int bytes_read, flag = 0;
        int fd_1 = open("File.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
        printf("Nhap noi dung muon ghi vao file duoi day (Bam Enter de ket thuc lan nhap):\n");
        while((bytes_read = read(0, bufferOpen, sizeof(bufferOpen)))>0){
            for (int i=0; i<bytes_read; i++){
                if(bufferOpen[i] == '\n'){
                    flag = 1;
                    break;
                }
            }
            write(fd_1, bufferOpen, bytes_read);
            if (flag){
                break;  
            }
        }
        printf("\n");
        printf("Tao va viet vao file thanh cong!\n");
        close(fd_1);
    }
    else if(i==2){
        char bufferOpen[512], bufferRead[512];
        int bytes_read, flag = 0;
        printf("Nhap ten file muon copy vao duoi day (Bam Enter de ket thuc lan nhap):\n");
        while((bytes_read = read(0, bufferOpen, sizeof(bufferOpen)))>0){
            for (int i=0; i<bytes_read; i++){
                if(bufferOpen[i] == '\n'){
                    bufferOpen[i] = '\0';
                    flag = 1;
                    break;
                }
            }
            if (flag){
                break;  
            }
        }
        int fd_1 = open(bufferOpen, O_RDONLY);
        int fd_2 = open("File.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
        while((bytes_read = read(fd_1, bufferRead, sizeof(bufferRead)))>0){
            write(fd_2, bufferRead, bytes_read);
        }
        printf("\n");
        printf("Tao va copy file thanh cong!\n");
        close(fd_1);
        close(fd_2);
    }
    else{
        printf("Nhap khong dung. Khoi dong lai chuong trinh va nhap lai!");
    }
}