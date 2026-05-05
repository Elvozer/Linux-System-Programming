#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

int ERR = 0, INF = 0;

bool Check_error(const char* input) {
    if (strstr(input, "error") != NULL || strstr(input, "ERROR") != NULL) {
        return true;
    }
    return false;
}

void handler(int signum) {
    if (signum == SIGINT) {
        printf("Stop the proceess\n");
    }
} 

int main() {
    signal(SIGINT, handler);
    int fd[2][2];
    pipe(fd[0]);
    pipe(fd[1]);
    char buffer_input[256];
    // Child process 1.
    if (fork() == 0) {
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[1][1]);
        char buffer[1024];
        int bytes_read;
        while ((bytes_read = read(fd[0][0], buffer, sizeof(buffer))) > 0) {
            ERR++;
            printf("Worker 1: Recognised new error\n");
            }
            close(fd[0][0]);
            // Exit process.
            exit(0);
    }
    // Child process 2.
    if (fork() == 0) {
            close(fd[1][1]);
            close(fd[0][0]);
            close(fd[0][1]);
            char buffer[1024];
            int bytes_read;
            while ((bytes_read = read(fd[1][0], buffer, sizeof(buffer))) > 0) {
                INF++;
                printf("Worker 1: Recognised new infor\n");
            }
            close(fd[1][0]);
            // Exit process.
            exit(0);
    }
    close(fd[1][0]);
    close(fd[0][0]);
    // Getting input.
    while (1) {
        int i = 0;
        printf("Write input:\n");
        if (fgets(buffer_input, sizeof(buffer_input), stdin) == NULL) {
            break;
        }
        // Take length of input.
        int len = strlen(buffer_input);
        // Take "\n" out of string.
        if (len > 0 && buffer_input[len - 1] == '\n') {
            buffer_input[len - 1] = '\0';
            len--;
        }
        if (len == 0) {
            break;
        }
        if (Check_error(buffer_input)) {
            write(fd[0][1], buffer_input, sizeof(buffer_input));
        } else {
            write(fd[1][1], buffer_input, sizeof(buffer_input));
        }
    }
    close(fd[0][1]);
    close(fd[1][1]);
    wait(NULL);
    wait(NULL);
    return 0;
}