#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 10
#define LIMIT_MIN 20
#define LIMIT_MAX 80

void mean_clipping(uint8_t *array, size_t size, uint8_t min, uint8_t max) {
    if (!array || size == 0) return;

    uint32_t sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += array[i];
    }

    uint8_t mean = sum / size;

    for (size_t i = 0; i < size; i++) {
        if (array[i] < min) {
            array[i] = min;
        } else if (array[i] > max) {
            array[i] = max;
        }
    }
}

int main() {
    uint8_t data[ARRAY_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    printf("Original data:\n");
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    mean_clipping(data, ARRAY_SIZE, LIMIT_MIN, LIMIT_MAX);

    printf("Data after mean clipping:\n");
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    return 0;
}
