#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 6
#define MAX_STACK_SIZE 100

typedef struct {
    short r;
    short c;
} element;

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
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else s->data[++(s->top)] = item;
}

element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
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

element here = { 1,0 }, entry = {1, 0};

char maze[MAZE_SIZE][MAZE_SIZE] = {
    { '1', '1', '1', '1', '1', '1' },
    { 'e', '0', '1', '0', '0', '1' },
    { '1', '0', '0', '0', '1', '1' },
    { '1', '0', '1', '0', '1', '1' },
    { '1', '0', '1', '0', '0', 'x' },
    { '1', '1', '1', '1', '1', '1' },
};

// 이동할 수 있는 위치를 스택에 삽입
void push_loc(StackType *s, int r, int c)
{
    if (r < 0 || c < 0) return;
    if (maze[r][c] != '1' && maze[r][c] != '.') {       // 이동할 수 없는 곳 또는 이미 방문한 곳
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}

// 미로를 화면에 출력한다.
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

int main(void)
{
    int r, c;
    StackType s;
    
    init_stack(&s);
    here = entry;
    while (maze[here.r][here.c] != 'x') {
        r = here.r;
        c = here.c;
        maze[r][c] = '.';       // 스택에 넣을 때 .으로 표시하는 것이 아니라 실제로 방문할 때 .으로 표시
        maze_print(maze);
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);
        if (is_empty(&s)) {
            printf("실패\n");
            return 0;
        }
        else
            here = pop(&s);
    }
    printf("성공\n");
    return 0;
}
