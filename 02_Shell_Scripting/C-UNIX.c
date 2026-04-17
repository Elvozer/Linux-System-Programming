#include<unistd.h>
#include<dirent.h>
#include<stdio.h>
#include<signal.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

void handler(int sig){
    printf("\n");
    printf("Program is terminated by user\n");
    exit(0);
}

int main(){
    signal(SIGINT, handler);
    while(1){
        DIR *ptrdir = opendir(".");
        struct dirent *filein4;
        while((filein4 = readdir(ptrdir)) != NULL){
            struct stat buf;
            stat(filein4->d_name, &buf);
            if ((filein4->d_name[0] != '.') && (S_ISREG(buf.st_mode))) printf("The file name is %s and it's size is %ld bytes\n",filein4->d_name, buf.st_size);
            else continue;
        }
        closedir(ptrdir);
        sleep(60);
    }
    return 0;
}