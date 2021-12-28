#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
    element key;
    struct TreeNode *left, *right;
} TreeNode;

// 새로운 노드를 생성하는 함수
TreeNode *new_node(int item) {
    TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// 삽입함수
TreeNode *insert_node(TreeNode *node, int key) {
    // 트리가 공백이면 새로운 노드를 반환한다.
    if (node == NULL) return new_node(key);
    
    // 그렇지 않으면 순환적으로 트리를 내려간다.
    if (key < node->key)
        node->left = insert_node(node->left, key);
    else if (key > node->key)
        node->right = insert_node(node->right, key);
    
    // 변경된 루트 포인터를 반환한다.
    return node;
}
