#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <malloc.h>
#define MAX_STACK_SIZE 100    // 스택의 최대 크기

typedef int element;
typedef struct {
    element *data;      // data는 포인터로 정의된다.
    int capacity;       // 현재 크기
    int top;
} StackType;

// 스택 생성 함수
void init_stack(StackType *s)
{
    s->top = -1;
    s->capacity = 1;
    s->data = (element *)malloc(s->capacity * sizeof(element));
} 

// 공백 상태 검출 함수
int is_empty(StackType *s)
{
    return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType *s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입 함수 -> 가장 많이 변한 함수, 공간이 부족하면 메모리를 2배로 더 확보함
void push(StackType *s, element item)
{
    if (is_full(s)) {
        s -> capacity *= 2;
        s -> data = (element *)realloc(s->data, s->capacity * sizeof(element));
    }
    s->data[++(s->top)] = item;
}

// 삭제 함수
element pop(StackType *s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}


// 피크 함수
element peek(StackType *s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[s->top];
}

int main(void)
{
    StackType s;

    init_stack(&s);

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));

    free(s.data);
    
    return 0;    
}
