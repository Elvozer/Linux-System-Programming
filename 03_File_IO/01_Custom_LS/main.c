#define _DEFAULT_SOURCE

#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>

int main(int argc, char *argv[]){
    if (argc != 2){
        perror("Loi cmnr nhap lai");
        return 1;
    }
    DIR *dir = opendir(argv[1]);
    if (dir == NULL){
        perror("Loi mo thu muc");
        return 1;
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL){
        if(entry->d_name[0] == '.') continue;
        if(entry->d_type == DT_DIR){
            printf("Directory is %s\n", entry->d_name);
        }
        else if(entry->d_type == DT_REG){
            printf("File is %s\n", entry->d_name);
        }
        else{
            printf("Unknown is %s\n", entry->d_name);
        }
    }
    closedir(dir);
    return 0;
}