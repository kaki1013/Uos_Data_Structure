#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

// 노드의 개수
int get_node_count(TreeNode *node) {
    int count = 0;
    if (node != NULL)
        count = 1 + get_node_count(node->left) + get_node_count(node->right);
    return count;
}

// 높이 구하기
int get_height(TreeNode *node) {
    int height = 0, max, left, right;
    
    if(node != NULL)
        left = get_height(node->left);
        right = get_height(node->right);
        max = (left > right) ? left : right;
        height = 1 + max;
    return height;
}

// 단말 노드 개수 구하기
int get_leaf_count(TreeNode *node) {
    int count = 0;
    
    if (node != NULL) {
        if (node->left == NULL && node->right == NULL)
            return 1;
        else
            count = get_leaf_count(node->left) + get_leaf_count(node->right);
    }
    return count;
}