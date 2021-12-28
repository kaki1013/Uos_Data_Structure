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

// 정렬된 상태로 삽입됨
ListNode* insert_sorted(ListNode* head, element value)
{
    ListNode *p = (ListNode*)malloc(sizeof(ListNode));
    ListNode *cur;

    p->data = value;
    p->link = NULL;

    if (head == NULL) {     // 빈 리스트라면, p가 head가 됨
        head = p;
        return head;
    }
    
    cur = head;
    while (cur->link != NULL && cur->link->data < p->data) {
        cur = cur->link;
    }
    // 마지막(cur=마지막 노드)이거나 더 큰 노드를 찾았을 때(cur = 더 큰 노드의 하나 이전 노드) 종료됨
    
    p->link = cur->link;
    cur->link = p;
    // cur - (cur->link) 에서 cur - p - (cur->link) 로 변경
    
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