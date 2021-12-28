#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode {      // 이중연결 노드 타입
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DListNode;

// 이중 연결 리스트를 초기화
void init(DListNode *phead)     // 헤드노드가 자신을 가리키도록 함
{
    phead->llink = phead;
    phead->rlink = phead;
}

// 이중 연결 리스트의 노드를 출력
void print_dlist(DListNode* phead)
{
    DListNode* p;
    
    for (p = phead->rlink; p != phead; p = p->rlink)
        printf("<-| |%d| |->", p->data);
    printf("\n");
}

// 새로운 데이터를 노드 before의 오른쪽에 삽입한다.
void dinsert(DListNode *before, element data)
{
    DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
    newnode->data =  data;  // strcpy(newnode->data, data);
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

// 노드 removed를 삭제한다.
void ddelete(DListNode* head, DListNode* removed)
{
    if (removed == head) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

// 실습 - 특정 값을 가지고 있는 노드를 검색해서 그 노드의 포인터를 반환하는 함수
DListNode* search(DListNode* phead, element data)
{
    for (DListNode* p = phead->rlink; p != phead; p = p->rlink) {
        if (p->data == data)
            return p;
    }
    return NULL;
}

// 이중 연결 리스트 테스트 프로그램
int main(void)
{
    DListNode* head = (DListNode *)malloc(sizeof(DListNode));
    element data;
    init(head);
    
    printf("추가 단계\n");
    for (int i = 0; i < 5; i++) {
        // 헤드 노드의 오른쪽에 삽입
        dinsert(head, i);
        print_dlist(head);
    }
    
    // 실습 - 검색
    printf("\n검색 값: ");
    scanf("%d", &data);
    if (search(head, data) != NULL)
        printf("%d is in list\n", data);
    else
        printf("%d is not in list\n", data);

    printf("\n삭제 단계\n");
    for (int i = 0; i < 5; i++) {
        print_dlist(head);
        ddelete(head, head->rlink);
    }
    free(head);
    return 0;
}