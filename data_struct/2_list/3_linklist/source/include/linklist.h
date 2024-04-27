#ifndef __LINKLIST_H_
#define __LINKLIST_H_

// 链表节点定义
typedef struct linknode_t {
    struct linknode_t *next;
} LinkListNode;

// 链表定义
typedef struct linklist_t {
    LinkListNode header;
    int length;
} LinkList;

// 初始化链表
LinkList *init_LinkList();

// 创造节点
LinkListNode *create_Node();

// 尾部添加节点
int *listnode_Append(LinkList *linklist, LinkListNode *node);

// 头部插入
int *listnode_Insert(LinkList *linklist);

// 查找结点
// -1 没有该数据
// 0 有该数据
int find_ListNode(LinkList *linklist, int find_node_data);

// 返回第index个结点
LinkListNode *get_ListNode(LinkList *linklist, int index);

// 打印链表数据
void print_LinkList(const LinkList *linklist);

// 排序链表，形成有序链表
LinkList *sort_LinkList(LinkList *linklist);

// 合并两个链表，形成有序链表
LinkList *merge_LinkList(LinkList *listA, LinkList *listB);

// 反转链表
LinkList *reverse_LinkList(LinkList *linklist);

// 返回值:
// 0成功释放
// -1释放错误
int deinit_LinkList(LinkList *linklist);

#endif // __LINKLIST_H_