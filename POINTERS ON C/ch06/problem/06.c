#include <stdio.h>

#define ARRAY_SIZE 32

void fun06() {
    int array[ARRAY_SIZE];
    int *pi;

    for (pi = &array[0]; pi < &array[ARRAY_SIZE];) 
        *++pi = 0;                                    // ++pi -> 数组的地址先增加一个元素单元地址,然后取地址所在的值
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("i:%d, array[%d]:%d\n", i, i, array[i]);
    }
}

int main(int argc, char const *argv[]) {
    fun06();

    return 0;
}

/*
** err 01:
** for (pi = &array[0]; pi < &array[ARRAY_SIZE];) 在数组中的ARRAY_SIZE 是表示数组中数据的个树；
** 比如array[5]是表示array数组中的数据个数是5个，从array[0]到array[4]；
** 明显pi < array[5] 已经越界
**
** err 02:
** *++pi = 0;
** ++的优先级高于*,所以先给pi+1，然后将结果拷贝，最后再对拷贝的值进行间接访问;
** 所以，当pi从a[0]开始时,实际上a[0]并没有清0,而是从a[1]开始的
**
*/