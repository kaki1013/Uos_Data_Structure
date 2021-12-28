#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 	8192    // 캐시 크기(캐시 블록의 개수)
#define TABLE_SIZE 	4001    // 해싱 테이블의 크기
#define TRUE 1
#define FALSE 0

typedef unsigned long element;
typedef struct cache_buffer {
    element blkno;          // 데이터 번호 in 참조 스트림
    struct cache_buffer *next, *prev;
    struct cache_buffer *hash_next, *hash_prev;
} Cache_Buffer;
typedef struct cache {		// 구조체 선언
	Cache_Buffer *head;		// FIFO를 위한 헤드노드 (큐처럼, 삽입된 순서대로 노드 관리)
	Cache_Buffer *hash_table[TABLE_SIZE];	// 해시 테이블 선언
	int count;				// 전체 캐시블록의 수(8192개가 넘었는지 체크하기 위함)
} Cache;

// 캐시 블록을 초기화: 헤드노드의 링크들이 자신을 가리키도록 함
void init_block(Cache_Buffer *p)
{
	p->blkno = -1;		// 헤드 노드일 경우 -1로 초기화하기 위함
    p->next = p;
    p->prev = p;
    p->hash_next = p;
    p->hash_prev = p;
}

// Cache 구조체를 초기화
void init(Cache *c)
{
	// 헤드 초기화
	c->head = (Cache_Buffer *)malloc(sizeof(Cache_Buffer));
	init_block(c->head);
	// 해시 테이블 초기화
	for (int i = 0; i < TABLE_SIZE; i++) {
		(c->hash_table)[i] = (Cache_Buffer *)malloc(sizeof(Cache_Buffer));
		init_block((c->hash_table)[i]);
	}
	// count 초기화
	c->count = 0;
}

// 캐시 블록이 8192개 모두 쓰였는지 확인
int is_full(Cache *c)
{
	return (c->count == CACHE_SIZE);
}

// 제산 함수를 사용한 해싱 함수
int hash_function(int key)
{
	return key % TABLE_SIZE;
}

// 체인법을 이용하여 테이블에서 키의 존재 여부 검사
int is_hash_in(Cache_Buffer *ht[], element num)
{
	int hash_value = hash_function(num);
	Cache_Buffer *bucket = ht[hash_value];
	Cache_Buffer *node;

	if (bucket->hash_next == bucket)	// 헤드노드만 존재하는 경우(해당 버킷의 슬롯이 0개)
		return FALSE;
	for (node = bucket->hash_next; node != bucket; node = node->hash_next)
		if (node->blkno == num)
			return TRUE;
	return FALSE;
}

// (존재 X 보장 후)cache 구조체에서 새로운 데이터를 해시 테이블에 삽입
void insert(Cache *c, element num)
{
	int hash_value = hash_function(num);	// 해시함수에 값 대입
	Cache_Buffer **ht = c->hash_table;
	Cache_Buffer *phead = c->head;
	// 삽입할 캐시 블록(노드) 생성
	Cache_Buffer *p;
	p = (Cache_Buffer *)malloc(sizeof(Cache_Buffer));
	p->blkno = num;
	// 해시 관련 링크 관리
	p->hash_prev = ht[hash_value]->hash_prev;
	p->hash_next = ht[hash_value];
	ht[hash_value]->hash_prev->hash_next = p;
	ht[hash_value]->hash_prev = p;
	// FIFO 위한 링크 관리
	p->prev = phead->prev;
	p->next = phead;
	phead->prev->next = p;
	phead->prev = p;
	// count 증가
	c->count++;
}

// 가장 예전에 삽입된 노드 삭제 for FIFO 리스트 관리
void delete(Cache *c)
{
	Cache_Buffer *removed = c->head->next;
	// FIFO 위한 링크 관리
	removed->prev->next = removed->next;
    removed->next->prev = removed->prev;
	// 해시 링크 관리
	removed->hash_prev->hash_next = removed->hash_next;
	removed->hash_next->hash_prev = removed->hash_prev;
	// count 감소
	c->count--;
	// romoved 할당 해제
    free(removed);
}

int main()
{
	int hit = 0, miss = 0;	// 캐시 히트율 측정용
	unsigned long num;
	Cache c;
	init(&c);

	FILE *fp;
	fp = fopen("test_trace.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "열 수 없음.\n");
		exit(1);
	}
	// 정상적으로 파일 열고난 후
	while (!feof(fp))
	{
		fscanf(fp, "%d", &num);				// 파일에서 입력 받기
		if (!is_hash_in(c.hash_table, num))	// 해시테이블에 존재하지 않으면..(존재하면 조회하고 끝)
		{
			if (is_full(&c))				// 가득 찼으면
				delete(&c);					// 가장 예전에 삽입된 노드 삭제
			insert(&c, num);				// 입력된 데이터 삽입(하고 조회..)
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