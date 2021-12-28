#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

void error(char *message)
{
    printf("%s\n", message);
    exit(1);
}

ListNode* insert_first(ListNode* head, element value)
{
    ListNode *p = (ListNode*)malloc(sizeof(ListNode));

    p->data = value;
    p->link = head;
    head = p;

    return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value)
{
    ListNode *p = (ListNode*)malloc(sizeof(ListNode));

    p->data = value;
    p->link = pre->link;
    pre->link = p;

    return head;
}

// ���ĵ� ���·� ���Ե�
ListNode* insert_sorted(ListNode* head, element value)
{
    ListNode *p = (ListNode*)malloc(sizeof(ListNode));
    ListNode *cur;

    p->data = value;
    p->link = NULL;

    if (head == NULL) {     // �� ����Ʈ���, p�� head�� ��
        head = p;
        return head;
    }
    
    cur = head;
    while (cur->link != NULL && cur->link->data < p->data) {
        cur = cur->link;
    }
    // ������(cur=������ ���)�̰ų� �� ū ��带 ã���� ��(cur = �� ū ����� �ϳ� ���� ���) �����
    
    p->link = cur->link;
    cur->link = p;
    // cur - (cur->link) ���� cur - p - (cur->link) �� ����
    
    return head;
}

ListNode* delete_first(ListNode* head)
{
    ListNode *to_be_removed;

    if (head == NULL)
        return NULL;

    to_be_removed = head;
    head = to_be_removed->link;
    free(to_be_removed);

    return head;
}

ListNode* delete(ListNode* head, ListNode* pre)
{
    ListNode *to_be_removed;

    to_be_removed = pre->link;
    pre->link = to_be_removed->link;
    free(to_be_removed);

    return head;
}

void print_list(ListNode* head)
{
    ListNode *p;

    for (p = head; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
}

int main() {
    ListNode* head = NULL;

    for (int i=0; i<5; i++) {
        head = insert_sorted(head, i);
        print_list(head);
    }

    head = insert_sorted(head, 8);
    print_list(head);
    head = insert_sorted(head, 7);
    print_list(head);
    head = insert_sorted(head, 6);
    print_list(head);

    for (int i=0; i<5; i++) {
        head = delete_first(head);
        print_list(head);
    }

    return 0;
}