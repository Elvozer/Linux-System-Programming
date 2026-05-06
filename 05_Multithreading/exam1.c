#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>

#define ARRAY_SIZE 1000
#define K 4

typedef struct {
    int id_thread;
    int start;
    int end;
    int *Arr;
} data_input;

typedef struct {
    int alert_count;
    int total_temp;
    int index_min;
    int id_thread;
    int local_min;
} data_output;

void *thread_func(void *arg) {
    data_input input = (*(data_input *)arg);
    // Initializes struct for output
    data_output *output = (data_output *)calloc(1, sizeof(data_output));
    // Initialize local_min
    output->local_min = input.Arr[input.start];
    // Check for infor
    printf("[Worker %d] Quét từ index %d đến %d. Hoàn tất!\n", input.id_thread, input.start, input.end);
    for (int i = input.start; i < input.end; i++) {
        if (input.Arr[i] >= 85) {
            output->alert_count++;
        }
        if (input.Arr[i] < output->local_min) {
            output->local_min = input.Arr[i];
            output->index_min = i; 
        }
        output->total_temp += input.Arr[i];
    }   
    output->id_thread = input.id_thread;
    return output;
}
int Arr[ARRAY_SIZE] = {0};

int main() {
    int total_alert = 0, index_min, temp_min, id_thread, chunk = ARRAY_SIZE / K; // Intialize variables for storing infor
    float ave_temp = 0;
    
    srand(time(NULL)); // seed random

    for (int i = 0; i < 1000; i++) {
        Arr[i] = rand() % 101; // random số nguyên
    }
    printf("[Main] Đã khởi tạo xong 1000 mẫu dữ liệu.\n");
    // Array stores id_thread
    pthread_t t[4];
    data_input infor_in[K];
    // Create 4 threads
    printf("[Main] Bắt đầu phân công cho 4 luồng...\n");
    for (int i = 0; i < K; i++) {
        infor_in[i].Arr = Arr;
        infor_in[i].id_thread = i;
        infor_in[i].start = i * chunk;
        infor_in[i].end = infor_in[i].start + chunk;
        pthread_create(&t[i], NULL, thread_func, &infor_in[i]);
    }
    // Initialize storing for address
    void *temp[K];
    data_output *infor_out[K];
    // Join thread
    for (int i = 0; i < K; i++) {
        pthread_join(t[i], &temp[i]);
    }
    for (int i = 0; i < K; i++) {
        infor_out[i] = (data_output *)temp[i];
        }
    // Summary output
    temp_min = infor_out[0]->local_min;
    index_min = infor_out[0]->index_min;
    id_thread = infor_out[0]->id_thread;
    for (int i = 0; i < K; i++) {
        total_alert += infor_out[i]->alert_count;
        ave_temp += infor_out[i]->total_temp;
        if (infor_out[i]->local_min < temp_min) {
            temp_min = infor_out[i]->local_min;
            index_min = infor_out[i]->index_min;
            id_thread = infor_out[i]->id_thread;
        } else if ((infor_out[i]->local_min == temp_min) && (infor_out[i]->index_min < index_min)) {
            index_min = infor_out[i]->index_min;
            id_thread = infor_out[i]->id_thread;
        }
    }
    ave_temp /= ARRAY_SIZE;
    printf("=== BÁO CÁO MÔI TRƯỜNG ===\n");
    printf("- Tổng số điểm cảnh báo nhiệt (>= 85 độ): %d điểm\n", total_alert);
    printf("- Nhiệt độ trung bình toàn khu vực: %f độ C\n", ave_temp);
    printf("- Nhiệt độ thấp nhất toàn cục: %d độ C\n", temp_min);
    printf("-> Xuất hiện lần đầu tại Index: %d (Tìm thấy bởi Worker %d)\n", index_min, id_thread);
    printf("==========================\n");
    for (int i = 0; i < K; i++) {
        free(infor_out[i]);
    }
    printf("[Main] Giải phóng bộ nhớ và kết thúc.\n");
    return 0;
}