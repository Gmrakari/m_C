#include "source/include/bak_LinkList.h"
#include <stdio.h>

static void pListA_test(void)
{
    TLinkList *pListA = initializeLinkedList();

    for (int i = 1; i < 11; i += 2) {
        append(pListA, i);
    }

    for (int i = 2; i < 10; i += 2) {
        insert(pListA, i);
    }

    printf("pListA->size:%d\r\n", (int)pListA->size);

    printLinkList(pListA);

    // sortLinkList(pListA);

    int key = 1;

    int res = -1;
    if (0 == (res = findNode(pListA, key))) {
        printf("find pListA exist value:%d\r\n", key);
    } else {
        printf("key:%d un exist\r\n", key);
    }
    
    key = 2;

    if (0 == (res = findNode(pListA, key))) {
        printf("find pListA exist value:%d\r\n", key);
    } else {
        printf("key:%d un exist\r\n", key);
    }

    // printf("%p\r\n", pListA);

    res = releaseLinkList(pListA);
    if (res != 0) {
        printf("releaseLinkList node failed!\r\n");
    } else {
        printf("releaseLinkList node successful!\r\n");
    }
    printf("%p\r\n", pListA);

    // printLinkList(pListA);

    res = releaseLinkList(pListA);
    if (res != 0) {
        printf("releaseLinkList node failed\r\n");
    } else {
        printf("releaseLinkList node successful!\r\n");
    }
    // printf("%p\r\n", pListA);

    return ;
}

static void pList_merge_test(void)
{
    TLinkList *pListA = initializeLinkedList();
    TLinkList *pListB = initializeLinkedList();

    int res = 0;

    res = releaseLinkList(pListA);
    if (res != 0) {
        printf("pListA releaseLinkList node failed\r\n");
    } else {
        printf("pListA releaseLinkList node successful!\r\n");
    }

    res = releaseLinkList(pListA);
    if (res != 0) {
        printf("pListA releaseLinkList node failed\r\n");
    } else {
        printf("pListA releaseLinkList node successful!\r\n");
    }

    res = releaseLinkList(pListB);
    if (res != 0) {
        printf("pListB releaseLinkList node failed\r\n");
    } else {
        printf("pListB releaseLinkList node successful!\r\n");
    }

    return ;
}

int main()
{
    // pListA_test();

    pList_merge_test();

    printf("hello world\r\n");
    return 0;
}
