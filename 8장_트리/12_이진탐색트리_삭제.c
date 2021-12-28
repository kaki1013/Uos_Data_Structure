#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
    element key;
    struct TreeNode *left, *right;
} TreeNode;

// �ּ� Ű���� ������ ��带 ã�Ƽ� ��ȯ
TreeNode * min_value_node(TreeNode * node) {
    TreeNode * current = node;
    
    // �� ���� �ܸ� ��带 ã���� ������
    while (current->left != NULL)
        current = current->left;
    
    return current;
}

// ���� Ž�� Ʈ���� Ű�� �־����� Ű�� ����� ��带 �����ϰ� ���ο� ��Ʈ ��带 ��ȯ�Ѵ�.
TreeNode * delete_node(TreeNode * root, int key) {
    if (root == NULL) return root;
    
    // ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
    if (key < root->key)
        root->left = delete_node(root->left, key);

    // ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
    else if (key > root->key)
        root->right = delete_node(root->right, key);

    // Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
    else {
        // ù ��°�� �� ��° ���
        if (root->left == NULL) {
            TreeNode * temp = root->right;
            free(root);
            return temp;
            }
        else if (root->right == NULL) {
            TreeNode * temp = root->left;
            free(root);
            return temp;
            }
        // �� ��° ���
        TreeNode * temp = min_value_node(root->right);

        // ������ ����Ʈ������ ���� ���� �� ã�Ƽ� �÷��ְ�, �÷��� ���� ����Ʈ������ ����
        // ���� ��ȸ�� �İ� ��带 �����Ѵ�.
        root->key = temp->key;
        // ���� ��ȸ�� �İ� ��带 �����Ѵ�.
        root->right = delete_node(root->right, temp->key);
        
    }
    return root;
}

