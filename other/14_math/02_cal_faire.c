#include <stdio.h>

int main() {
    #if 0
    // float totalAmount = 4.75;
    float totalAmount = 3.5;
    // int totalSeconds = 9 * 3600 + 29 * 60 + 43;
    int totalSeconds = 6 * 3600 + 56 * 60 + 35;

    float hourlyRate = totalAmount / (totalSeconds / 3600.0);
    float halfHourlyRate = hourlyRate / 2.0;

    printf("每小时费用: $%.2f\n", hourlyRate);
    printf("每30分钟费用: $%.2f\n", halfHourlyRate);

    #endif

    float per_Amount = 6.65;
    float times1 = 30;
    float times2 = 60;
    float total_amount = per_Amount * times1;
    float total_amount2 = per_Amount * times2;

    printf("费用: $%.2f\n", total_amount);
    printf("费用: $%.2f\n", total_amount2);

    return 0;
}
