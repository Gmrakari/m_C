#include "template_demo.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common.h"
#include "fragment_send.h"
#include "fragment_recv.h"
#include "message_queue.h"
// #include "common.h"



// 全局消息队列
message_queue_t send_queue;
message_queue_t recv_queue;

// 发送回调函数
int send_callback(uint8_t *data, uint32_t len) {
    message_queue_enqueue(&send_queue, data, len);
    return 0;
}

// 模拟发送线程
void *sender_thread(void *arg) {
    printf("[%s][%d] send Thread started\r\n", __func__, __LINE__);
    
    while (1) {
        uint8_t *data;
        uint32_t len;

        if (message_queue_dequeue(&send_queue, &data, &len) != 0) {
            continue;
        }
        
        // 模拟发送延迟
        usleep(10000); // 10ms
        
        // 模拟90%的传输成功率
        if (rand() % 100 < 90) {
            message_queue_enqueue(&recv_queue, data, len);
        } else {
            printf("[%s][%d]Packet lost!\r\n", __func__, __LINE__);
        }

        free(data);
    }printf("[%s][%d]\r\n", __func__, __LINE__);
    
    return NULL;
}

// 接收处理线程
void *receiver_thread(void *arg) {
    printf("[%s][%d][Receiver] Thread started\r\n", __func__, __LINE__);
    
    package_msg_t package_info;
    init_package_info(&package_info);
    
    while (1) {
        uint8_t *data;
        uint32_t len;
        
        if (message_queue_dequeue(&recv_queue, &data, &len) != 0) {
            continue;
        }
        
        uint8_t last_frag;
        int total_len;
        char *out;
        int olen;
        
        // 处理分片数据 (跳过cmd字节)
        int ret = fragment_receive(data + 1, len - 1, &last_frag, 
                                 &total_len, &out, &olen, &package_info);

        if (ret == 0) {
            printf("[Receiver] Message received! Length: %d\n", olen);
            print_data("Received data", (uint8_t *)out, olen);
            free(out);
        } else if (ret == -2) {
            printf("[Receiver] Fragment received, waiting for more...\n");
        } else {
            printf("[%s][%d][Receiver] Error processing fragment, ret: %d\r\n", __func__, __LINE__, ret);
        }

        free(data);
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    return NULL;
}

// int main() {
int test_main_func() {
    srand(time(NULL));
    
    // 初始化消息队列
    message_queue_init(&send_queue);
    message_queue_init(&recv_queue);
    
    // 创建发送和接收线程
    pthread_t network_tid, receiver_tid;
    pthread_create(&network_tid, NULL, sender_thread, NULL);
    pthread_create(&receiver_tid, NULL, receiver_thread, NULL);
    
    // 测试不同大小的数据包
    // int test_sizes[] = {100, 500, 479, 1024, 1500};
    int test_sizes[] = {256, 512};
    int num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);
    printf("[%s][%d]\r\n", __func__, __LINE__);
    for (int i = 0; i < num_tests; i++) {
        int size = test_sizes[i];
        uint8_t *data = malloc(size);
        generate_test_data(data, size);
        
        printf("\n[Test] Sending data size: %d\n", size);
        print_data("Original data", data, size);
        
        fragment_send(data, size, 0x01, send_callback);
        free(data);
        
        sleep(1); // 等待处理
    }printf("[%s][%d]\r\n", __func__, __LINE__);
    
    // 清理
    pthread_cancel(network_tid);printf("[%s][%d]\r\n", __func__, __LINE__);
    pthread_cancel(receiver_tid);printf("[%s][%d]\r\n", __func__, __LINE__);
    pthread_join(network_tid, NULL);printf("[%s][%d]\r\n", __func__, __LINE__);
    pthread_join(receiver_tid, NULL);printf("[%s][%d]\r\n", __func__, __LINE__);
    
    message_queue_destroy(&send_queue);printf("[%s][%d]\r\n", __func__, __LINE__);
    message_queue_destroy(&recv_queue);printf("[%s][%d]\r\n", __func__, __LINE__);
    
    printf("\nAll tests completed!\n");
    return 0;
}

int demo_app(void)
{
    test_main_func();
    printf("[%s][%d]\r\n", __func__, __LINE__);

    return 0;
}