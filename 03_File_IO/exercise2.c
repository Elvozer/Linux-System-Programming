#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    // 1. Mở file có cả quyền đọc/ghi, TẠO MỚI nếu chưa có, XÓA TRẮNG nếu đã có
    int fd1 = open("input.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd1 == -1){
        perror("Loi tao file input");
        return 1;
    }

    char buf1[] = "Hello, World!";
    // 2. Tự tin ghi vào mà không cần check if loằng ngoằng
    write(fd1, buf1, 13);
    
    // 3. Tua lại con trỏ về đầu
    lseek(fd1, 0, SEEK_SET);

    // ... Đoạn copy sang output.txt của m ...
    int fd2 = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char buf2[1024];
    int bytesRead;
    while((bytesRead = read(fd1, buf2, 10)) > 0){
        write(fd2, buf2, bytesRead);
    }

    printf("Input file: input.txt\n");
    printf("Output file: output.txt\n");
    close(fd1);
    close(fd2);
    return 0;
}