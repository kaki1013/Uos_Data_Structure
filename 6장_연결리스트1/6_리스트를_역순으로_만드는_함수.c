#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

typedef int element;
typedef struct ListNode {   // ��� Ÿ��
    element data;
    struct ListNode *link;
} ListNode;

ListNode* insert_first(ListNode *head, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

void print_list(ListNode *head)
{
    for (ListNode *p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL\n");
}

ListNode* reverse(ListNode *head)
{
    // ��ȸ �����ͷ� p, q, r�� ���
    ListNode *p, *q, *r;

    p = head;   // �������� ���� ����Ʈ
    q = NULL;   // �������� ���� ���
    while (p != NULL) {
        // r�� q, q�� p�� ���ʷ� ���󰣴�.
        r = q;  // r�� �������� �� ����Ʈ
        q = p;
        p = p->link;
        q->link = r;    // q�� ��ũ ������ �ٲ۴�.
    }
    return q;
    
}

// �׽�Ʈ ���α׷�
int main(void)
{
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    head1 = insert_first(head1, 10);
    head1 = insert_first(head1, 20);
    head1 = insert_first(head1, 30);
    print_list(head1);

    head2 = reverse(head1);
    print_list(head2);

    return 0;
}