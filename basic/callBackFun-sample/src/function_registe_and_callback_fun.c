#include "header.h"

void callbackFun(int event) {
    switch(event) {
        case 1:
            printf("ABCDEFG\n"); break;
        case 2:
            printf("abcdefg\n"); break;
        case 3:
            printf("1234567\n"); break;
        case 4:
            printf("7654321\n"); break;
        default:
            printf("new event:%d\n", event); break;
    }
}

void main() {
    int event = 0;
    int ret;
    Compute_ST ptrComputer;
    ptrComputer.index = 1;
    ptrComputer.function = callbackFun;

    ret = registerCallBackFun(&ptrComputer);
    if (ret == -1) {
        printf("registe fun failed\n");
    }
    for (;;) {
        printf("Enter number:");
        scanf("%d", &event);

        if (event == 0) return ;
        
        // 触发事件
        mgmtbFun(event);
    }
    return ;
}
