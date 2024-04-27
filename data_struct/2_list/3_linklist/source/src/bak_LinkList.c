#include "../include/bak_LinkList.h"

#include <stdlib.h> // malloc
#include <stdio.h>
#include <string.h> // memset

/*
** 链表节点定义
** typedef struct _tag_linknode_t {
**     struct _tag_linknode_t *next;
**     int data; 
** } LinkList_Node;
**
** 链表定义
** typedef struct _tag_linklist_t {
**     struct _tag_linknode_t *head;
**     size_t size;
** } TLinkList;
**
*/

// 初始化链表
TLinkList *initializeLinkedList(void)
{
    TLinkList *list = (TLinkList*)malloc(sizeof(TLinkList));
    if (!list) {
        printf("initializeLinkedList err\r\n");
        exit(1);
    }
    list->head = NULL;
    list->size = 0;
    printf("initializeLinkedList successful\r\n");
    return list;
}

// 创造节点
LinkList_Node *createNode(int value)
{
    LinkList_Node *newNode = (LinkList_Node*)malloc(sizeof(LinkList_Node));
    if (!newNode) {
        printf("createNode err\r\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

// 头部添加节点
TLinkList *append(TLinkList *list, int data)
{
    LinkList_Node *newNode = createNode(data);
    LinkList_Node *current = list->head;

    if (!current) {
        list->head = newNode;
    } else {
        while (current->next)
            current = current->next;
        current->next = newNode;
    }

    list->size++;
    return list;
}

// TLinkList *insert(TLinkList *list, int data)
// {
//     LinkList_Node *newNode = createNode(data);
//     if (!list->head) {
//         list->head = newNode;
//     } else {
//         newNode->next = list->head;
//         list->head = newNode;
//     }
//     list->size++;
//     return list;
// }

TLinkList *insert(TLinkList *list, int data)
{
    LinkList_Node *newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
    return list;
}

// 查找结点
// -1 没有该数据
// 0 有该数据
int findNode(TLinkList *list, int find_node_data)
{
    if (!list) {
        printf("list param err\r\n");
        exit(1);
    }

    const LinkList_Node *node = list->head;
    int key = find_node_data;
    while (node) {
        if (node->data == key) {
            return 0;
        }
        node = node->next;
    }
    return -1;
}

// 打印链表数据
void printLinkList(const TLinkList *list)
{
    if (!list || !list->head) {
        printf ("printLinkList failed, list is null!\r\n");
        // exit(1);
        return ;
    }

    printf("list node num:%d\r\n", (int)list->size);

    const LinkList_Node *node = list->head;
    while (node) {
        printf("%d", node->data);
        node = node->next;
        if (node) {
            printf("->");
        }
    }
    printf("\r\n");
}

int swapValue(int *a, int *b)
{
    if (!a || *b) {
        printf("param err\r\n");
        exit(1);
    }
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_arr(int *arr, int len)
{
    if (!arr || len < 0) return ;

    for (int i = 0; i < len; i++) {
        printf("arr[%d]:%d ", i, arr[i]);
    }
    printf("\r\n");
}


// 排序链表，形成有序链表
TLinkList *sortLinkList(TLinkList *list)
{
    if (!list) {
        printf ("list param err\r\n");
        exit(1);
    }

    int listLen = list->size;
    if (listLen == 1) return list;

    int *dataList = (int*)malloc(sizeof(int) * listLen);
    if (!dataList) {
        printf("malloc err\r\n");
        exit(1);
    }

    memset(dataList, 0, sizeof(int) * listLen);
    int index = 0;

    LinkList_Node *node = list->head;
    while (node) {
        *(dataList + index) = node->data;
        index++;
        node = node->next;
    }

    print_arr(dataList, listLen);

    if (dataList) { free(dataList); dataList = NULL;}
}

// 合并两个链表，形成有序链表
TLinkList *mergeLinkList(TLinkList *listA, TLinkList *listB);

// 返回值:
// 0成功释放
// -1释放错误
int releaseLinkList(TLinkList *list)
{
    int ret = 0;

    if (!list || !list->head) {
        printf("list is null, releaseLinkList failed!\r\n");
        ret = -1;
        return ret;
    }

    LinkList_Node *current = list->head;

    while (current) {
        LinkList_Node *node = current;
        if (node) { free(node); node = NULL; }
        current = current->next;
    }

    { free(list); list->head = NULL; list = NULL; }

    return ret;
}
