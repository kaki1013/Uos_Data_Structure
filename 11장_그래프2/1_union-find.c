#define MAX_VERTICES 100

int parent[MAX_VERTICES];		// 부모 노드
							// 초기화
void set_init(int n) {
	for (int i = 0; i<n; i++) 
		parent[i] = -1;
}

// curr가 속하는 집합을 반환한다.
int set_find(int curr) {
	if (parent[curr] == -1)
		return curr; 			// 루트 
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

// 두개의 원소가 속한 집합을 합친다.
void set_union(int a, int b) {
	int root1 = set_find(a);	// 노드 a의 루트를 찾는다. 
	int root2 = set_find(b);	// 노드 b의 루트를 찾는다. 
	if (root1 != root2) 	// 합한다. 
		parent[root1] = root2;
}
