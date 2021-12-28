#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

typedef int element;
typedef struct ListNode {   // ��� Ÿ��
    element data;
    struct ListNode *link;
} ListNode;

// ���� ó�� �Լ�
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// ���� ����
ListNode* insert_first(ListNode *head, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

// ��� pre �ڿ� ���ο� ��� ����
ListNode* insert(ListNode *head, ListNode *pre, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

// ���� ����
ListNode* delete_first(ListNode *head)
{
    ListNode *removed;
    if (head == NULL) return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

// pre�� ����Ű�� ����� ���� ��带 ����
ListNode* delete(ListNode *head, ListNode *pre)
{
    ListNode *removed;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

// �湮 ���� �ڵ�
void print_list(ListNode *head)
{
    for (ListNode *p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL\n");
}

// �׽�Ʈ ���α׷�
int main(void)
{
    ListNode *head = NULL;
    
    for (int i = 0; i < 5; i++) {
        head = insert_first(head, i);
        print_list(head);
    }
 
    for (int i = 0; i < 5; i++) {
        head = delete_first(head);
        print_list(head);
    }
    
    return 0;
}

/*
6.4 �ܼ� ���� ����Ʈ
// ����� ����
typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

// ����Ʈ�� ����
ListNode *head = NULL;

head = (ListNode *)malloc(sizeof(ListNode));

head->data = 10;
head->link = NULL;

// 2��° ��� ����
ListNode *p;

p = (ListNode *)malloc(sizeof(ListNode));

p->data = 20;
p->link = NULL;

// ����� ����
head->link = p;

6.5 �ܼ� ���� ����Ʈ�� ���� ����
// ���� ����
ListNode* insert_first(ListNode *head, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

// ��� pre �ڿ� ���ο� ��� ����
ListNode* insert(ListNode *head, ListNode *pre, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

// ���� ����
ListNode* delete_first(ListNode *head)
{
    ListNode *removed;
    if (head == NULL) return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

// pre�� ����Ű�� ����� ���� ��带 ����
ListNode* delete(ListNode *head, ListNode *pre)
{
    ListNode *removed;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

// �湮 ���� �ڵ�
void print_list(ListNode *head)
{
    for (ListNode *p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL\n");
}

*/