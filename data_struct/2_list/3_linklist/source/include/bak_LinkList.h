#ifndef _BAK_LINKLIST_H_
#define _BAK_LINKLIST_H_

#include <stdio.h>  // size_t

#define LINKLIST_TYPE int

// 链表节点定义
typedef struct tag_linknode_t {
    struct tag_linknode_t *next;
    LINKLIST_TYPE data;
} LinkList_Node;

// 链表定义
typedef struct tag_linklist_t {
    struct tag_linknode_t *head;
    int size;
} TLinkList;
 
// 初始化链表
TLinkList *initializeLinkedList();

// 创造节点
LinkList_Node *createNode(LINKLIST_TYPE value);

// 尾部添加节点
TLinkList *append(TLinkList *list, LINKLIST_TYPE data);

// 头部插入
TLinkList *insert(TLinkList *list, LINKLIST_TYPE data);

// 查找结点
// -1 没有该数据
// 0 有该数据
int findNode(TLinkList *list, LINKLIST_TYPE find_node_data);

// 返回第index个结点
LinkList_Node *getNode(TLinkList *list, int index);

// 打印链表数据
void printLinkList(const TLinkList *list);

// 排序链表，形成有序链表
TLinkList *sortLinkList(TLinkList *list);

// 合并两个链表，形成有序链表
TLinkList *mergeLinkList(TLinkList *listA, TLinkList *listB);

// 返回值:
// 0成功释放
// -1释放错误
int releaseLinkList(TLinkList *list);

#endif // _BAK_LINKLIST_H_