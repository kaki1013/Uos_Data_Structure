#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType *s) {
    s->top = -1;
} 

int is_empty(StackType *s) {
    return (s->top == -1);
}

int is_full(StackType *s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item) {
    if (is_full(s)) {
        printf("overflow\n");
        exit(1);
        return;
    }
    else s->data[++(s->top)] = item;
}

element pop(StackType *s) {
    if (is_empty(s)) {
        printf("underflow\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}

element peek(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[s->top];
}

int size(StackType *s) {
    return s->top + 1;
}

int main(void)
{
    int i;
    char line[128];
    StackType s;

    init_stack(&s);
    printf("input string!\n");
    gets(line);

    for (i=0; i<(strlen(line)/2); i++)
        push(&s, line[i]);

    for (i=(int)(strlen(line) / 2.0 + 0.5); i < strlen(line); i++) {
        if (pop(&s) != line[i]) {
            printf("No\n");
            return -1;
        }
    }

    printf("Yes!\n");

    return 0;
}