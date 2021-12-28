#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode {      // ���߿��� ��� Ÿ��
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DListNode;

// ���� ���� ����Ʈ�� �ʱ�ȭ
void init(DListNode *phead)     // ����尡 �ڽ��� ����Ű���� ��
{
    phead->llink = phead;
    phead->rlink = phead;
}

// ���� ���� ����Ʈ�� ��带 ���
void print_dlist(DListNode* phead)
{
    DListNode* p;
    
    for (p = phead->rlink; p != phead; p = p->rlink)
        printf("<-| |%d| |->", p->data);
    printf("\n");
}

// ���ο� �����͸� ��� before�� �����ʿ� �����Ѵ�.
void dinsert(DListNode *before, element data)
{
    DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
    newnode->data =  data;  // strcpy(newnode->data, data);
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

// ��� removed�� �����Ѵ�.
void ddelete(DListNode* head, DListNode* removed)
{
    if (removed == head) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

// �ǽ� - Ư�� ���� ������ �ִ� ��带 �˻��ؼ� �� ����� �����͸� ��ȯ�ϴ� �Լ�
DListNode* search(DListNode* phead, element data)
{
    for (DListNode* p = phead->rlink; p != phead; p = p->rlink) {
        if (p->data == data)
            return p;
    }
    return NULL;
}

// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
    DListNode* head = (DListNode *)malloc(sizeof(DListNode));
    element data;
    init(head);
    
    printf("�߰� �ܰ�\n");
    for (int i = 0; i < 5; i++) {
        // ��� ����� �����ʿ� ����
        dinsert(head, i);
        print_dlist(head);
    }
    
    // �ǽ� - �˻�
    printf("\n�˻� ��: ");
    scanf("%d", &data);
    if (search(head, data) != NULL)
        printf("%d is in list\n", data);
    else
        printf("%d is not in list\n", data);

    printf("\n���� �ܰ�\n");
    for (int i = 0; i < 5; i++) {
        print_dlist(head);
        ddelete(head, head->rlink);
    }
    free(head);
    return 0;
}