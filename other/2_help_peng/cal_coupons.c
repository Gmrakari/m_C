#include <stdio.h>

// 查找优惠券的索引
void _find_coupon_index(int total, int arr[], int arr_len, int *index)
{
    // 金额小于等于0，数组为空，数组长度为0，出错处理
    if (total <= 0 || arr == NULL || arr_len < 0) {
        goto _exit;
    }

	for (int i = 0;i < arr_len; i++) {
        // 如果商品的价格不满足优惠券，不做操作
        if (total < arr[0]) {
            goto _exit;
        }

        // 如果商品的价格超过满减的最大值，直接能使用最大优惠券
        if (total >= arr[arr_len - 1]) {
            *index = arr_len - 1;
            return ;
        }

        // 如果刚好满足，直接返回使用的优惠券的索引
        if (total == arr[i]) {
            *index = i;
            return ;
        }

        // 查找使用哪张优惠券
        if (total > arr[i] && total < arr[i + 1]) {
            *index = i;
            return ;
        }
	}
_exit:
    *index = -1;
}

void test() {
    // 优惠券数组
    int arr1[] = {120, 240, 360, 480, 600};

    // 满减区间
    int arr2[] = {3000, 6000, 9000, 12000, 16000};

    int arr_len = sizeof(arr2) / sizeof(arr2[0]);

    // 测试金额,测试数据
    int total[] = {-1, 0, 2999, 3000, 3001, 5999, 6000, 6001, 8999, 90001, 11999, 12999, 15999, 16999};

    // 查找优惠券的索引
    int index = 0; 

    for (int i = 0; i < sizeof(total) / sizeof(total[0]); i++) {
        printf("[%d] start to test tatal:%d\r\n", i, total[i]);

        // 调用查找优惠券的索引函数 
        _find_coupon_index(total[i], arr2, arr_len, &index);

        if (index != -1) {
            printf("use coupon index:%d is $:%d\r\n", index, arr1[index]);
        } else {
            printf("disable use coupon\r\n");
        }
        index = -1;// 测试完一边，恢复index的值

        printf("===========\r\n\r\n");
    }
}

int main() {
    test();
}
