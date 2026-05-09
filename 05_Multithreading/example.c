#include<pthread.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
#include<ctype.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int total_vowels = 0;

void handle_sigint(int sig) {
    handle_sigusr1();
    return NULL;
}

void handle_sigusr1() {
    printf("Total vowels is: %d\n", total_vowels);
    return NULL;
}

void *thread_A(void *arg) {
    char *str = (char *)arg;
    printf("The array is: ");
    for (int i = 0; i < strlen(str); i++) {
        printf("%c ", str[i] - 32);
    }
    return NULL;
}

void *thread_B(void *arg) {
    char *str = (char *)arg;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        char c = tolower(str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            pthread_mutex_lock(&lock);
            total_vowels++;
            pthread_mutex_unlock(&lock);
        }
    }
}

int main() {
    signal(SIGINT, handle_sigint);
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    if (fork() == 0) {
        signal(SIGUSR1, handle_sigusr1);
        close(fd2[0]);
        close(fd2[1]);
        close(fd1[1]);
        char buffer[1024];
        int bytes_read;
        while ((bytes_read = read(fd1[0], buffer, sizeof(buffer))) > 0);
        close(fd1[0]);
        exit(0);
    }

    if (fork() == 0) {
        
    }
}