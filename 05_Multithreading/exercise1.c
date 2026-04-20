#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<unistd.h>
#include<stdlib.h>

int n;

void *sortArr1(void *arg){
    int *Arr = (int *)arg;
    for(int i = 0; i<n/2-1; i++){
        for(int j=i+1; j<n/2; j++){
            if(*(Arr+i) > *(Arr+j)){
                int temp = *(Arr+j);
                *(Arr+j) = *(Arr+i);
                *(Arr+i) = temp;
            }
        }
    }
    return NULL;
}
int *merge(int *A){
    int *res = (int *)malloc(sizeof(int)*n);
    int *fir1 = A;
    int *fir2 = A+n/2;
    int i = 0;
    while(fir1<A+n/2 || fir2<A+n){
        if(fir1<A+n/2 && fir2>=A+n){
            res[i++] = *(fir1++);
        }
        else if(fir2<A+n && fir1>=A+n/2){
            res[i++] = *(fir2++);
        }
        else if(*fir1 < *fir2){
            res[i++] = *(fir1);
            fir1++;
        }
        else{
            res[i++] = *(fir2);
            fir2++; 
        }
    }
    return res;
}
void *sortArr2(void *arg){
    int *Arr = (int *)arg;
    for(int i = n/2; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(*(Arr+i) > *(Arr+j)){
                int temp = *(Arr+j);
                *(Arr+j) = *(Arr+i);
                *(Arr+i) = temp;
            }
        }
    }
    return NULL;
}

int main(){
    printf("Nhập số phần tử: \n");
    scanf("%d", &n);
    int A[n];
    printf("Nhập từng số vào mảng: \n");
    for(int i=0; i<n; i++){
        scanf("%d", &A[i]);
    }
    pthread_t t1, t2;
    pthread_create(&t1, NULL, sortArr1, A);
    pthread_create(&t2, NULL, sortArr2, A);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    int *res = merge(A);
    printf("Mảng đã sắp xếp là:\n");
    for(int i=0; i<n; i++){
        printf("%d ", res[i]);
    }
    printf("\n");
    return 0;
}