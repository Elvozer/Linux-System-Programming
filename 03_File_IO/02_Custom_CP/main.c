#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){
    if (argc != 3){
        perror("Loi me roi");
        return 1;
    }
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd1 < 0 || fd2 < 0){
        perror("loi");
        return 1;
    }
    int bytes_read;
    char buffer[512];
    while((bytes_read = read(fd1, buffer, 2)) > 0){
        write(fd2, buffer, bytes_read);
    }
    close(fd1);
    close(fd2);
    return 0;
}