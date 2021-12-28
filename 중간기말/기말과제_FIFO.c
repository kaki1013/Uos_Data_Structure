#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 	8192    // ĳ�� ũ��(ĳ�� ����� ����)
#define TABLE_SIZE 	4001    // �ؽ� ���̺��� ũ��
#define TRUE 1
#define FALSE 0

typedef unsigned long element;
typedef struct cache_buffer {
    element blkno;          // ������ ��ȣ in ���� ��Ʈ��
    struct cache_buffer *next, *prev;
    struct cache_buffer *hash_next, *hash_prev;
} Cache_Buffer;
typedef struct cache {		// ����ü ����
	Cache_Buffer *head;		// FIFO�� ���� ����� (ťó��, ���Ե� ������� ��� ����)
	Cache_Buffer *hash_table[TABLE_SIZE];	// �ؽ� ���̺� ����
	int count;				// ��ü ĳ�ú���� ��(8192���� �Ѿ����� üũ�ϱ� ����)
} Cache;

// ĳ�� ����� �ʱ�ȭ: ������� ��ũ���� �ڽ��� ����Ű���� ��
void init_block(Cache_Buffer *p)
{
	p->blkno = -1;		// ��� ����� ��� -1�� �ʱ�ȭ�ϱ� ����
    p->next = p;
    p->prev = p;
    p->hash_next = p;
    p->hash_prev = p;
}

// Cache ����ü�� �ʱ�ȭ
void init(Cache *c)
{
	// ��� �ʱ�ȭ
	c->head = (Cache_Buffer *)malloc(sizeof(Cache_Buffer));
	init_block(c->head);
	// �ؽ� ���̺� �ʱ�ȭ
	for (int i = 0; i < TABLE_SIZE; i++) {
		(c->hash_table)[i] = (Cache_Buffer *)malloc(sizeof(Cache_Buffer));
		init_block((c->hash_table)[i]);
	}
	// count �ʱ�ȭ
	c->count = 0;
}

// ĳ�� ����� 8192�� ��� �������� Ȯ��
int is_full(Cache *c)
{
	return (c->count == CACHE_SIZE);
}

// ���� �Լ��� ����� �ؽ� �Լ�
int hash_function(int key)
{
	return key % TABLE_SIZE;
}

// ü�ι��� �̿��Ͽ� ���̺��� Ű�� ���� ���� �˻�
int is_hash_in(Cache_Buffer *ht[], element num)
{
	int hash_value = hash_function(num);
	Cache_Buffer *bucket = ht[hash_value];
	Cache_Buffer *node;

	if (bucket->hash_next == bucket)	// ����常 �����ϴ� ���(�ش� ��Ŷ�� ������ 0��)
		return FALSE;
	for (node = bucket->hash_next; node != bucket; node = node->hash_next)
		if (node->blkno == num)
			return TRUE;
	return FALSE;
}

// (���� X ���� ��)cache ����ü���� ���ο� �����͸� �ؽ� ���̺� ����
void insert(Cache *c, element num)
{
	int hash_value = hash_function(num);	// �ؽ��Լ��� �� ����
	Cache_Buffer **ht = c->hash_table;
	Cache_Buffer *phead = c->head;
	// ������ ĳ�� ���(���) ����
	Cache_Buffer *p;
	p = (Cache_Buffer *)malloc(sizeof(Cache_Buffer));
	p->blkno = num;
	// �ؽ� ���� ��ũ ����
	p->hash_prev = ht[hash_value]->hash_prev;
	p->hash_next = ht[hash_value];
	ht[hash_value]->hash_prev->hash_next = p;
	ht[hash_value]->hash_prev = p;
	// FIFO ���� ��ũ ����
	p->prev = phead->prev;
	p->next = phead;
	phead->prev->next = p;
	phead->prev = p;
	// count ����
	c->count++;
}

// ���� ������ ���Ե� ��� ���� for FIFO ����Ʈ ����
void delete(Cache *c)
{
	Cache_Buffer *removed = c->head->next;
	// FIFO ���� ��ũ ����
	removed->prev->next = removed->next;
    removed->next->prev = removed->prev;
	// �ؽ� ��ũ ����
	removed->hash_prev->hash_next = removed->hash_next;
	removed->hash_next->hash_prev = removed->hash_prev;
	// count ����
	c->count--;
	// romoved �Ҵ� ����
    free(removed);
}

int main()
{
	int hit = 0, miss = 0;	// ĳ�� ��Ʈ�� ������
	unsigned long num;
	Cache c;
	init(&c);

	FILE *fp;
	fp = fopen("test_trace.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "�� �� ����.\n");
		exit(1);
	}
	// ���������� ���� ���� ��
	while (!feof(fp))
	{
		fscanf(fp, "%d", &num);				// ���Ͽ��� �Է� �ޱ�
		if (!is_hash_in(c.hash_table, num))	// �ؽ����̺� �������� ������..(�����ϸ� ��ȸ�ϰ� ��)
		{
			if (is_full(&c))				// ���� á����
				delete(&c);					// ���� ������ ���Ե� ��� ����
			insert(&c, num);				// �Էµ� ������ ����(�ϰ� ��ȸ..)
			miss++;
		}
		else
			hit++;
	}
	fclose(fp);
	
	int total = hit + miss;
	float hit_ratio = (float)hit/(hit+miss), miss_ratio = (float)miss/(hit+miss);
	printf("hit ratio = %f, miss ratio = %f\n", hit_ratio, miss_ratio);
	printf("\n");
	printf("tatal access = %d, hit = %d, miss = %d\n", total, hit, miss);
	printf("Hit ratio = %f\n", hit_ratio);
    return 0;
}