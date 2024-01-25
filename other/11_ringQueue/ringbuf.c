#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct {
    uint32_t size;
    uint32_t head;
    uint32_t tail;
    uint8_t *buffer;
} ring_buffer_t;

// 初始化环形缓冲区
void init_ring_buffer(ring_buffer_t *ring_buf, uint32_t size) {
    ring_buf->size = size;
    ring_buf->head = 0;
    ring_buf->tail = 0;
    ring_buf->buffer = (uint8_t *)malloc(size);
}

// 销毁环形缓冲区
void destroy_ring_buffer(ring_buffer_t *ring_buf) {
    free(ring_buf->buffer);
    ring_buf->buffer = NULL;
}

// 向环形缓冲区写入1个数据
void write_to_buffer(ring_buffer_t *ring_buf, uint8_t data) {
    if ((ring_buf->tail + 1) % ring_buf->size != ring_buf->head) {
        ring_buf->buffer[ring_buf->tail] = data;
        ring_buf->tail = (ring_buf->tail + 1) % ring_buf->size;
    }
}

// 向环形缓冲区写入n个数据
void write_n_to_buffer(ring_buffer_t *ring_buf, const uint8_t *data, uint32_t num_to_write) {
    for (uint32_t i = 0; i < num_to_write; ++i) {
        write_to_buffer(ring_buf, data[i]);
    }
}

// 从环形缓冲区读取1个数据
uint32_t read_from_buffer(ring_buffer_t *ring_buf, uint8_t *data) {
    if (ring_buf->head != ring_buf->tail) {
        *data = ring_buf->buffer[ring_buf->head];
        ring_buf->head = (ring_buf->head + 1) % ring_buf->size;
        return 1;
    }
    return 0; // Buffer is empty
}

// 从环形缓冲区读取指定数量的数据
uint32_t read_n_from_buffer(ring_buffer_t *ring_buf, uint8_t *data, uint32_t num_to_read) {
    uint32_t read_count = 0;

    while (read_count < num_to_read && ring_buf->head != ring_buf->tail) {
        data[read_count] = ring_buf->buffer[ring_buf->head];
        ring_buf->head = (ring_buf->head + 1) % ring_buf->size;
        ++read_count;
    }

    return read_count;
}

// 读取缓冲区的全部内容
uint32_t read_all_from_buffer(ring_buffer_t *ring_buf, uint8_t *data) {
    return read_n_from_buffer(ring_buf, data, ring_buf->size);
}

int main() {
    ring_buffer_t my_buffer;
    init_ring_buffer(&my_buffer, 10);  // Initialize a buffer of size 10

    // Writing data to the buffer
    uint8_t write_data[] = {1, 2, 3, 4, 5};
    write_n_to_buffer(&my_buffer, write_data, sizeof(write_data));

    // Reading 1 element from the buffer
    uint8_t read_data;
    if (read_from_buffer(&my_buffer, &read_data)) {
        printf("Read 1 element: %d\n", read_data);
    } else {
        printf("Buffer is empty.\n");
    }

    write_n_to_buffer(&my_buffer, write_data, sizeof(write_data));

    // Reading 3 elements from the buffer
    uint8_t read_data_3[3];
    uint32_t read_count_3 = read_n_from_buffer(&my_buffer, read_data_3, 3);
    printf("Read 3 elements: ");
    for (uint32_t i = 0; i < read_count_3; ++i) {
        printf("%d ", read_data_3[i]);
    }
    printf("\n");

    // Reading all elements from the buffer
    uint8_t read_data_all[10];
    uint32_t read_count_all = read_all_from_buffer(&my_buffer, read_data_all);
    printf("Read all elements: ");
    for (uint32_t i = 0; i < read_count_all; ++i) {
        printf("%d ", read_data_all[i]);
    }
    printf("\n");

    // Writing 1 element to the buffer
    write_to_buffer(&my_buffer, 6);

    write_n_to_buffer(&my_buffer, write_data, sizeof(write_data));

    // Writing 2 elements to the buffer
    uint8_t write_data_2[] = {7, 8};
    write_n_to_buffer(&my_buffer, write_data_2, sizeof(write_data_2));

    // Reading all elements from the buffer
    uint8_t read_data_final[10];
    uint32_t read_count_final = read_all_from_buffer(&my_buffer, read_data_final);
    printf("Read final elements: ");
    for (uint32_t i = 0; i < read_count_final; ++i) {
        printf("%d ", read_data_final[i]);
    }
    printf("\n");

    destroy_ring_buffer(&my_buffer);  // Clean up

    return 0;
}
