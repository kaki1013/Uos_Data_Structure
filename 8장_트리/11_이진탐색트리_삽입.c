#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
    element key;
    struct TreeNode *left, *right;
} TreeNode;

// ���ο� ��带 �����ϴ� �Լ�
TreeNode *new_node(int item) {
    TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// �����Լ�
TreeNode *insert_node(TreeNode *node, int key) {
    // Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.
    if (node == NULL) return new_node(key);
    
    // �׷��� ������ ��ȯ������ Ʈ���� ��������.
    if (key < node->key)
        node->left = insert_node(node->left, key);
    else if (key > node->key)
        node->right = insert_node(node->right, key);
    
    // ����� ��Ʈ �����͸� ��ȯ�Ѵ�.
    return node;
}
