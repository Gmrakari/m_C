#include <stdio.h>
#include <stdint.h>
#include <math.h>

// usage:
// gcc rms.c -lm

#define ARRAY_SIZE 10

double calculate_rms(uint8_t *array, size_t size) {
    if (!array || size == 0) return 0;

    uint32_t sum_of_squares = 0;
    for (size_t i = 0; i < size; i++) {
        sum_of_squares += (uint32_t)array[i] * array[i];
    }

    return sqrt((double)sum_of_squares / size);
}

int main() {
    uint8_t data[ARRAY_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    printf("Original data:\n");
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    double rms = calculate_rms(data, ARRAY_SIZE);

    printf("Root Mean Square (RMS) value: %.2f\n", rms);

    return 0;
}
