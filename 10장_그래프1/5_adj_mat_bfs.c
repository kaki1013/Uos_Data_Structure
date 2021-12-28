#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10

typedef int element;
typedef struct {                 // 큐 타입
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} QueueType;
 
// 오류 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
 
void init_queue(QueueType *q)
{
    q->rear = -1;
    q->front = -1;
}

void queue_print(QueueType *q)
{
    for (int i = 0; i<MAX_QUEUE_SIZE; i++) {
        if (i <= q->front || i> q->rear)
            printf("   | ");
        else
            printf("%d | ", q->data[i]);
    }
    printf("\n");
}

int is_full(QueueType *q)
{
    if (q->rear == MAX_QUEUE_SIZE - 1)
        return 1;
    else
        return 0;
}

int is_empty(QueueType *q)
{
    if (q->front == q->rear)
        return 1;
    else
        return 0;
}

void enqueue(QueueType *q, int item)
{
    if (is_full(q)) {
        error("큐가 포화상태입니다.");
        return;
    }
    q->data[++(q->rear)] = item;
}
 
int dequeue(QueueType *q)
{
    if (is_empty(q)) {
        error("큐가 공백상태입니다.");
        return -1;
    }
    int item = q->data[++(q->front)];
    return item;
}

#define MAX_VERTICES 50
typedef struct GraphType {
    int n;    // 정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int visited[MAX_VERTICES];

// 그래프 초기화
void init(GraphType* g) {
    int r, c;
    g->n = 0;
    for (r = 0; r<MAX_VERTICES; r++)
        for (c = 0; c<MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->n++;
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

// 인접 행렬 출력 함수
void print_adj_mat(GraphType *g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%2d ", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}

// 인접 행렬 bfs
void bfs_mat(GraphType* g, int v) {
    int w;
    QueueType q;

    init_queue(&q);     // 큐 초기화
    visited[v] = TRUE;          // 정점 v 방문 표시
    printf("%d  방문 -> ", v);
    enqueue(&q, v);            // 시작 정점을 큐에 저장
    while (!is_empty(&q)) {
        v = dequeue(&q);        // 큐에 정점 추출
        for (w = 0; w<g->n; w++)    // 인접 정점 탐색
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = TRUE;    // 방문 표시
                printf("%d 방문 -> ", w);
                enqueue(&q, w);     // 방문한 정점을 큐에 저장
        }
    }
}

int main() {
    GraphType *g;    
    g = (GraphType *)malloc(sizeof(GraphType));
    init(g);
    for(int i=0;i<6;i++)
        insert_vertex(g, i);
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 0, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 1, 5);

    printf("너비 우선 탐색\n");
    bfs_mat(g, 0);
    printf("\n");
    free(g);
    return 0;
}