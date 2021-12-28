#include <stdio.h>
#include <stdlib.h>
 
#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10

typedef int element;
typedef struct {                 // ť Ÿ��
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} QueueType;
 
// ���� �Լ�
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
        error("ť�� ��ȭ�����Դϴ�.");
        return;
    }
    q->data[++(q->rear)] = item;
}
 
int dequeue(QueueType *q)
{
    if (is_empty(q)) {
        error("ť�� ��������Դϴ�.");
        return -1;
    }
    int item = q->data[++(q->front)];
    return item;
}

#define MAX_VERTICES 50
typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;
typedef struct GraphType {
    int n;    // ������ ����
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

// �׷��� �ʱ�ȭ
void init(GraphType* g) {
    int v;
    g->n = 0;
    for (v = 0; v<MAX_VERTICES; v++)
        g->adj_list[v] = NULL;
}

// ���� ���� ����
void insert_vertex(GraphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�");
        return;
    }
    g->n++;
}

// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType* g, int u, int v) {
    GraphNode* node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����");
        return;
    }
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

// ���� ����Ʈ ��� �Լ�
void print_adj_mat(GraphType *g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* p = g->adj_list[i];
        printf("���� %d�� ���� ����Ʈ ", i);
        while (p != NULL) {
            printf("-> %d ", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
}

// ���� ����Ʈ�� ǥ���� �׷����� ���� ���� �켱 Ž��
void bfs_list(GraphType* g, int v) {
    GraphNode* w;
    QueueType q;
    
    init_queue(&q);                    // ť �ʱ� ȭ
    visited[v] = TRUE;      // ���� v �湮 ǥ��
    printf("%d �湮 -> ", v);
    enqueue(&q, v);            // ���������� ť�� ����
    while (!is_empty(&q)) {
        v = dequeue(&q);        // ť�� ����� ���� ����
        for (w = g->adj_list[v]; w; w = w->link) //���� ���� Ž��
            if (!visited[w->vertex]) {    // �̹湮 ���� Ž��
                visited[w->vertex] = TRUE;   // �湮 ǥ��
                printf("%d �湮 -> ", w->vertex);
                enqueue(&q, w->vertex);    //������ ť�� ����
        }
    }
}

int main() {
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    init(g);
    for(int i=0;i<4;i++)
        insert_vertex(g, i);
    insert_edge(g, 0, 1);
    insert_edge(g, 1, 0);
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 0);
    insert_edge(g, 0, 3);
    insert_edge(g, 3, 0);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 2);
    bfs_list(g, 0);
    free(g);
    return 0;
}