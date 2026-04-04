#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){
    int i;
    printf("Hay lua chon che do tao file:\n1. Tao file va viet noi dung vao file tu ban phim.\n2. Tao file va copy noi dung tu file khac vao.\nLua chon: ");
    scanf("%d", &i);
    while(getchar() != '\n');
    if(i==1){
        char bufferOpen[512];
        int bytes_read, flag = 0;
        FILE *filePtr = fopen("File.txt", "wb");
        printf("Nhap noi dung muon ghi vao file duoi day (Bam Enter de ket thuc lan nhap):\n");
        fgets(bufferOpen, sizeof(bufferOpen), stdin);
        fputs(bufferOpen, filePtr);
        printf("\n");
        printf("Tao va viet vao file thanh cong!\n");
        fclose(filePtr);
    }
    else if(i==2){
        char bufferOpen[512], bufferRead[512];
        int bytes_read, flag = 0;
        printf("Nhap ten file muon copy vao duoi day (Bam Enter de ket thuc lan nhap):\n");
        fgets(bufferOpen, sizeof(bufferOpen), stdin);
        int len = strlen(bufferOpen);
        for(int i=0; i<len; i++){
            if(bufferOpen[i] == '\n'){
                bufferOpen[i] = '\0';
                break;
            }
        }
        FILE *firPtr = fopen(bufferOpen, "rb");
        FILE *secPtr = fopen("File.txt", "wb");
        while((bytes_read = fread(bufferRead, 1, sizeof(bufferRead), firPtr))>0){
            fwrite(bufferRead, 1, bytes_read, secPtr);
        }
        printf("\n");
        printf("Tao va copy file thanh cong!\n");
        fclose(firPtr);
        fclose(secPtr);
    }
    else{
        printf("Nhap khong dung. Khoi dong lai chuong trinh va nhap lai!");
    }
}