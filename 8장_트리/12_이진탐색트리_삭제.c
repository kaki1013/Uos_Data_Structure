#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
    element key;
    struct TreeNode *left, *right;
} TreeNode;

// 최소 키값을 가지는 노드를 찾아서 반환
TreeNode * min_value_node(TreeNode * node) {
    TreeNode * current = node;
    
    // 맨 왼쪽 단말 노드를 찾으러 내려감
    while (current->left != NULL)
        current = current->left;
    
    return current;
}

// 이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고 새로운 루트 노드를 반환한다.
TreeNode * delete_node(TreeNode * root, int key) {
    if (root == NULL) return root;
    
    // 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
    if (key < root->key)
        root->left = delete_node(root->left, key);

    // 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
    else if (key > root->key)
        root->right = delete_node(root->right, key);

    // 키가 루트와 같으면 이 노드를 삭제하면 됨
    else {
        // 첫 번째나 두 번째 경우
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
        // 세 번째 경우
        TreeNode * temp = min_value_node(root->right);

        // 오른쪽 서브트리에서 가장 작은 값 찾아서 올려주고, 올려준 값은 서브트리에서 삭제
        // 중위 순회시 후계 노드를 복사한다.
        root->key = temp->key;
        // 중위 순회시 후계 노드를 삭제한다.
        root->right = delete_node(root->right, temp->key);
        
    }
    return root;
}

