#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

typedef int element;
typedef struct ListNode {   // 노드 타입
    element data;
    struct ListNode *link;
} ListNode;

// 오류 처리 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 삽입 연산
ListNode* insert_first(ListNode *head, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert(ListNode *head, ListNode *pre, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

// 삭제 연산
ListNode* delete_first(ListNode *head)
{
    ListNode *removed;
    if (head == NULL) return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

// pre가 가리키는 노드의 다음 노드를 삭제
ListNode* delete(ListNode *head, ListNode *pre)
{
    ListNode *removed;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

// 방문 연산 코드
void print_list(ListNode *head)
{
    for (ListNode *p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL\n");
}

// 테스트 프로그램
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
6.4 단순 연결 리스트
// 노드의 정의
typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

// 리스트의 생성
ListNode *head = NULL;

head = (ListNode *)malloc(sizeof(ListNode));

head->data = 10;
head->link = NULL;

// 2번째 노드 생성
ListNode *p;

p = (ListNode *)malloc(sizeof(ListNode));

p->data = 20;
p->link = NULL;

// 노드의 연결
head->link = p;

6.5 단순 연결 리스트의 연산 구현
// 삽입 연산
ListNode* insert_first(ListNode *head, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert(ListNode *head, ListNode *pre, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

// 삭제 연산
ListNode* delete_first(ListNode *head)
{
    ListNode *removed;
    if (head == NULL) return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

// pre가 가리키는 노드의 다음 노드를 삭제
ListNode* delete(ListNode *head, ListNode *pre)
{
    ListNode *removed;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

// 방문 연산 코드
void print_list(ListNode *head)
{
    for (ListNode *p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL\n");
}

*/